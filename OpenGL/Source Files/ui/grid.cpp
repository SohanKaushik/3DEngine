#include "pch.h"
#include "grid.h"

ui::Grid::Grid(): m_size(1000), m_spacing(5.0f), m_color(glm::vec3(0.3, 0.3, 0.3)), m_dMin(10.0f), m_dMax(300.0f)  
{}

void ui::Grid::render()
{
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    float halfSize = m_size;

    unsigned int index = 0;

    for (float x = -halfSize; x <= halfSize; x += m_spacing) {
        // Add vertices for lines parallel to the Z-axis
        vertices.push_back(glm::vec3(x, 0.0f, -halfSize));
        vertices.push_back(glm::vec3(x, 0.0f, halfSize));

        // Add indices for the line
        indices.push_back(index++);
        indices.push_back(index++);
    };


    for (float z = -halfSize; z <= halfSize; z += m_spacing) {
        // Add vertices for lines parallel to the X-axis
        vertices.push_back(glm::vec3(-halfSize, 0.0f, z));
        vertices.push_back(glm::vec3(halfSize, 0.0f, z));

        // Add indices for the line
        indices.push_back(index++);
        indices.push_back(index++);
    }

    // Create or update the vertex-index buffer
    //mVertexIndexBuffer = std::make_unique<Render::VertexIndexBuffer>(vertices, indices);
    mVertexIndexBuffer = std::make_unique<render::VertexIndexBuffer>();
    mVertexIndexBuffer->create(vertices, indices);

};

void ui::Grid::destroy()
{
    mVertexIndexBuffer->destroy();
};
