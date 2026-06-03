#pragma once
// Cube object class

#include "glm/glm.hpp"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class Cube {
private:
    glm::vec3 position;
    glm::vec3 rotation;

    // The cube class will also hold the vertex buffer, the layout, the index buffer and shader
    VertexBuffer vb;
    VertexBufferLayout layout;
    IndexBuffer ib;
    Shader shader;

    // The cube needs to hold the mvp matrix
    glm::mat4 mvp;
public:
    Cube();
    Cube(glm::vec3 position, glm::vec3 rotation);
    ~Cube();

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);

    glm::vec3 getPosition();
    glm::vec3 getRotation();
};