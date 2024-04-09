#include "test_texture_2d.h"

#include "renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    TestTexture2D::TestTexture2D() : translation_a(200, 200, 0), translation_b(400, 200, 0), va(), layout(), vb(positions, 4 * 4 * sizeof(float)), ib(indices, 6), shader("res/shaders/texture.shader"), texture("res/textures/pikachu.png")
    {

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        layout.push<float>(2);
        layout.push<float>(2);
        va.addBuffer(vb, layout);

        proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
        shader.bind();
        shader.setUniform1i("u_Texture", 0);
        texture.bind();

        va.unbind();
        shader.unbind();
        vb.unbind();
        ib.unbind();
    }

    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::onUpdate(float deltaTime)
    {
    }

    void TestTexture2D::onRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        shader.bind();

        Renderer renderer;
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_a);
            glm::mat4 mvp = proj * view * model;
            shader.setUniformMat4f("u_MVP", mvp);
            renderer.draw(va, ib, shader);
        }
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translation_b);
            glm::mat4 mvp = proj * view * model;
            shader.setUniformMat4f("u_MVP", mvp);
            renderer.draw(va, ib, shader);
        }
    }

    void TestTexture2D::onImGuiRender()
    {
        static float f = 0.0f;
        ImGui::SliderFloat3("Translation A", &translation_a.x, 0.0f, 960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::SliderFloat3("Translation B", &translation_b.x, 0.0f, 960.0f); // Edit 1 float using a slider from 0.0f to 1.0f
    }
}