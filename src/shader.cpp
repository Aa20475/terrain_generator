#include "shader.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "renderer.h"

Shader::Shader(const std::string& filepath)
:m_FilePath(filepath){
    ShaderProgramSource source = parseShader(m_FilePath);
    m_RendererID = createShader(source.vertexSource, source.fragmentSource);
}

Shader::~Shader(){
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const{
    GLCall(glUseProgram(0));
}

ShaderProgramSource Shader::parseShader(const std::string &filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::compileShader(const std::string &source, unsigned int type)
{
    GLCall(unsigned int id = glCreateShader(type));
    const char *src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char *message = (char *)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = compileShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float f2, float f3){
    GLCall(glUniform4f(getUniformLocation(name), v0,v1,f2,f3)); // Set the color uniform
}

void Shader::setUniform1f(const std::string& name, float value){
    GLCall(glUniform1f(getUniformLocation(name), value)); // Set the color uniform
}

void Shader::setUniform1i(const std::string& name, int value){
    GLCall(glUniform1i(getUniformLocation(name), value)); // Set the color uniform
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matr){
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matr[0][0]));
}


int Shader::getUniformLocation(const std::string& name){
    if(m_UniformLocationCache.find(name)!=m_UniformLocationCache.end())return m_UniformLocationCache[name];
    GLCall(int uniform_location = glGetUniformLocation(m_RendererID, name.c_str())); 
    if(uniform_location == -1) std::cout << "Warning: uniform "<<name<<" doesn't exist!"<<std::endl;

    m_UniformLocationCache[name] = uniform_location;
    return uniform_location;
}