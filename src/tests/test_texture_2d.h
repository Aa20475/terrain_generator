#pragma once

#include "test.h"
#include "shader.h"
#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"

namespace test{
    class TestTexture2D : public Test {
    public:
        TestTexture2D();
        ~TestTexture2D();

        void onUpdate(float deltaTime) override;
        void onRender() override;
        void onImGuiRender() override;
    private:
        glm::vec3 translation_a,translation_b;    

        float positions[16] = {
            200.0f, 200.0f, 0.0f, 0.0f, // 0
            500.0f, 500.0f, 1.0f, 1.0f,  // 1
            500.0f, 200.0f, 1.0f, 0.0f, // 2
            200.0f, 500.0f, 0.0f, 1.0f // 3
        };

        unsigned int indices[6] = {
            0, 1, 2,
            0, 1, 3};

        Shader shader;
        Texture texture;
        VertexArray va;
        VertexBuffer vb;
        VertexBufferLayout layout;
        IndexBuffer ib;
        glm::mat4 proj;
        glm::mat4 view;
        

    };
}