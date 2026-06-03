#include "cube.h"
#include "glm/glm.hpp"

Cube::Cube() {
    // The cube will be initialized at the origin
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotation = glm::vec3(0.0f, 0.0f, 0.0f);

    // The vertex buffer will be initialized with cube's 8 3d vertices
    float coordinates[24] = {
        -0.5f, -0.5f, -0.5f, // 0
        -0.5f, 0.5f, -0.5f, // 1
        0.5f, 0.5f, -0.5f, // 2
        0.5f, -0.5f, -0.5f, // 3
        -0.5f, -0.5f, 0.5f, // 4
        -0.5f, 0.5f, 0.5f, // 5
        0.5f, 0.5f, 0.5f, // 6
        0.5f, -0.5f, 0.5f // 7
    };
    unsigned int indices[36] = {
        0, 1, 2, 2, 3, 0, // front
        1, 5, 6, 6, 2, 1, // top
        7, 6, 5, 5, 4, 7, // back
        4, 0, 3, 3, 7, 4, // bottom
        4, 5, 1, 1, 0, 4, // left
        3, 2, 6, 6, 7, 3 // right
    };

    vb = VertexBuffer(coordinates, 24 * sizeof(float));
    ib = IndexBuffer(indices, 36);
    layout.push<float>(3);

    shader = Shader("res/shaders/basic.shader");
    shader.bind();
    shader.setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

}