#include "pch.h"

#include "Object.h"


// Constructor that sets up the object
Object::Object(glm::vec3 pos, glm::vec3 col)
    : position(pos), color(col), m_model(glm::translate(glm::mat4(1.0f), pos))
{
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    // Generate cube vertices and indices
    CubeData(vertices, indices);

    // Create and bind vertex/index buffers
    //mVertexIndexBuffer->bind();
    mVertexIndexBuffer->create(vertices, indices);

    // Store index count for rendering
    indexCount = indices.size();

    // Unbind buffers
    mVertexIndexBuffer->unbind();
}


void Object::CubeData(
    std::vector<glm::vec3>& positions,
    std::vector<unsigned int>& indices) {
    // Cube positions
    positions = {
        // Front face
        {-1.0f, -1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f},
        // Back face
        {-1.0f, -1.0f, -1.0f}, {-1.0f,  1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f},
        // Left face
        { 1.0f, -1.0f, -1.0f}, { 1.0f,  1.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}, { 1.0f, -1.0f,  1.0f},
        // Right face
        {-1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f,  1.0f}, {-1.0f,  1.0f,  1.0f}, {-1.0f,  1.0f, -1.0f},
        // Top face
        {-1.0f,  1.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}, { 1.0f,  1.0f, -1.0f}, {-1.0f,  1.0f, -1.0f},
        // Bottom face
        {-1.0f, -1.0f,  1.0f}, {-1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f, -1.0f}, { 1.0f, -1.0f,  1.0f}
    };

    //// Cube normals
    //normals = {
    //    // Front face
    //    { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f}, { 0.0f,  0.0f, -1.0f},
    //    // Back face
    //    { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f}, { 0.0f,  0.0f,  1.0f},
    //    // Left face
    //    {-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f}, {-1.0f,  0.0f,  0.0f},
    //    // Right face
    //    { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f}, { 1.0f,  0.0f,  0.0f},
    //    // Top face
    //    { 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f}, { 0.0f, -1.0f,  0.0f},
    //    // Bottom face
    //    { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}, { 0.0f,  1.0f,  0.0f}
    //};

    //// Cube texture coordinates
    //texCoords = {
    //    // Front face
    //    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    //    // Back face
    //    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    //    // Left face
    //    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    //    // Right face
    //    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    //    // Top face
    //    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f},
    //    // Bottom face
    //    {0.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f}, {0.0f, 1.0f}
    //};

    // Cube indices
    indices = {
        0, 1, 2,  2, 3, 0,  // Front face
        4, 5, 6,  6, 7, 4,  // Back face
        8, 9, 10, 10, 11, 8, // Left face
        12, 13, 14, 14, 15, 12, // Right face
        16, 17, 18, 18, 19, 16, // Top face
        20, 21, 22, 22, 23, 20  // Bottom face
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



