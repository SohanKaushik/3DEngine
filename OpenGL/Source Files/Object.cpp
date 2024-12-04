#include "Object.h"
#include <glad/glad.h>  // For OpenGL functions
#include <GLFW/glfw3.h> // For GLFW functions
#include <glm/ext/matrix_transform.hpp>

// Constructor that sets up the object
Object::Object(glm::vec3 pos, glm::vec3 col) : position(pos), color(col) {
    m_model = glm::translate(glm::mat4(1.0f), pos);

    // Generate cube data (vertices, indices)
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    CubeData(vertices, indices);
    indexCount = indices.size();

    // Create and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Create and bind EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture Co:ordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind VAO
    glBindVertexArray(0);
}

// Utility function to generate cube vertices and indices
void Object::CubeData(std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    vertices = {
        // Positions          // Normals         // Texture Coords
        // Front face
        -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,

        // Back face
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,

        // Left face
         1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         
        // Right face
         -1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         -1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         -1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         -1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         
        // Top face
         -1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
          1.0f,  1.0f,  1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
          1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         -1.0f,  1.0f, -1.0f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         
        // Bottom face
         -1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
         -1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
          1.0f, -1.0f, -1.0f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
          1.0f, -1.0f,  1.0f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    indices = {
        0, 1, 2,  2, 3, 0,  // Front face
        4, 5, 6,  6, 7, 4,  // Back face
        8, 9, 10,  10, 11, 8, // Left face
        12, 13, 14,  14, 15, 12, // Right face
        16, 17, 18,  18, 19, 16, // Top face
        20, 21, 22,  22, 23, 20  // Bottom face
    };

}

void Object::SetModelPosition(glm::vec3 position, Shader& shader)
{
    m_model = glm::translate(glm::mat4(1.0f), position);
    shader.SetUniformMat4f("model", m_model);
};


void Object::SetModelScale(glm::vec3 scale) {
    m_model = glm::scale(m_model, scale);
};



