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
        float positions[12] = {
            -0.5f, -0.5f, // 0
            0.5f, 0.5f,   // 1
            0.5f, -0.5f,  // 2
            -0.5f, 0.5f,  // 3
        };

        unsigned int indices[6] = {
            0, 1, 2,
            0, 1, 3};

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.push<float>(2);
        va.addBuffer(vb,layout);

        IndexBuffer ib(indices, 6);
        Shader shader("res/shaders/basic.shader");

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
            shader.setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f); // Set the color uniform
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