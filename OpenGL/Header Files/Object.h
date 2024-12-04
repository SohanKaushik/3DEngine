#pragma once
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp> 
#include <vector>
#include <Shader.h>

struct Object {
    glm::vec3 position;
    glm::vec3 color;
    glm::mat4 m_model = glm::translate(glm::mat4(1.0f), position);
    unsigned int VAO, VBO, EBO;
    int indexCount;

    Object(glm::vec3 pos, glm::vec3 color);
    void CubeData(std::vector<float>& vertices, std::vector<unsigned int>& indices);
    void SetModelPosition(glm::vec3 position, Shader& shader);
    void SetModelScale(glm::vec3 scale);
};
