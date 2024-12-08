#pragma once
#include "pch.h"

#include <shader/shader.h>
#include "render/VertexIndexBuffer.h"

struct Object {
    glm::vec3 position;
    glm::vec3 color;
    glm::mat4 m_model = glm::translate(glm::mat4(1.0f), position);
    int indexCount = 0;

    Object(){}
    Object(glm::vec3 pos, glm::vec3 color);
    void CubeData(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices);
    glm::vec3 GetPosition() { return position; }
    void SetModelPosition(glm::vec3 position, Shader& shader);
    void SetModelScale(glm::vec3 scale);

private:
    std::unique_ptr<render::VertexIndexBuffer> mVertexIndexBuffer = std::make_unique<render::VertexIndexBuffer>();
};
