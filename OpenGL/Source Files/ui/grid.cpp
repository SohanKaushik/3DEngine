#include "pch.h"
#include "grid.h"

ui::Grid::Grid(): m_size(1000), m_spacing(5.0f), m_color(glm::vec3(0.3, 0.3, 0.3)), m_dMin(10.0f), m_dMax(300.0f)  
{}

// Generate vertices and indices
std::vector<glm::vec3> vertices;
std::vector<unsigned int> indices;

void ui::Grid::Init() {

    float halfSize = m_size;
    unsigned int index = 0;

    for (float x = -halfSize; x <= halfSize; x += m_spacing) {
        vertices.push_back(glm::vec3(x, 0.0f, -halfSize));
        vertices.push_back(glm::vec3(x, 0.0f, halfSize));
        indices.push_back(index++);
        indices.push_back(index++);
    }

    for (float z = -halfSize; z <= halfSize; z += m_spacing) {
        vertices.push_back(glm::vec3(-halfSize, 0.0f, z));
        vertices.push_back(glm::vec3(halfSize, 0.0f, z));
        indices.push_back(index++);
        indices.push_back(index++);
    }

    // Create the VertexIndexBuffer
    mVertexIndexBuffer = std::make_unique<render::VertexIndexBuffer>();
    mVertexIndexBuffer->create(vertices, indices);
};

void ui::Grid::render(Shader& shader) {
    if (!mVertexIndexBuffer) {
        std::cerr << "Error: VertexIndexBuffer not initialized.\n";
        return;
    }

    // Bind the shader and set uniforms
    shader.use();
    shader.SetUniformMat4f("model", glm::mat4(1.0f)); // Grid's model matrix
    shader.SetUniform3fv("uColor", glm::vec3(0.8f, 0.8f, 0.8f)); // Grid color

    // Draw the grid
    mVertexIndexBuffer->bind();
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, nullptr);
    mVertexIndexBuffer->unbind();
}


//void ui :: Grid::SetGridUniforms() {
//
//};

void ui::Grid::destroy()
{
    mVertexIndexBuffer->destroy();
};
