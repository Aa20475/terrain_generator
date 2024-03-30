#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "renderer.h"
#include "vertex_buffer_layout.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow *window;
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1); // Enable VSync

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

    // Triangle vertices
    {
        float positions[] = {
            200.0f, 200.0f, 0.0f, 0.0f, // 0
            500.0f, 500.0f, 1.0f, 1.0f,  // 1
            500.0f, 200.0f, 1.0f, 0.0f, // 2
            200.0f, 500.0f, 0.0f, 1.0f // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 1, 3};

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.push<float>(2);
        layout.push<float>(2);
        va.addBuffer(vb,layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);

        Shader shader("res/shaders/texture.shader");
        shader.bind();
        shader.setUniform1i("u_Texture", 0);
        shader.setUniformMat4f("u_MVP", proj);

        Texture texture("res/textures/pikachu.png");
        texture.bind();

        va.unbind();
        shader.unbind();
        vb.unbind();
        ib.unbind();

        Renderer renderer;
        
        float r = 0.0f;
        float increment = 0.05f;
        while (!glfwWindowShouldClose(window))
        {
            renderer.clear();

            shader.bind();
            renderer.draw(va, ib, shader);

            if (r > 1.0f)
            {
                increment = -0.05f;
            }
            else if (r < 0.0f)
            {
                increment = 0.05f;
            }

            r += increment;

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}