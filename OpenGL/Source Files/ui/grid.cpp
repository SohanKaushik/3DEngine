#include "pch.h"
#include "grid.h"

ui::Grid::Grid(): m_size(1000), m_spacing(5.0f), m_color(glm::vec3(0.4, 0.4, 0.4)), m_dMin(10.0f), m_dMax(300.0f)  
{}

void ui::Grid::Init()
{   
    std::cout << "grid" << std::endl;

    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;
    int gridSize = m_size;

    glm::vec3 xColor = glm::vec3(0.886, 0.376, 0.357); //red
    glm::vec3 yColor = glm::vec3(0.482, 0.8, 0.482);

    glm::vec3 lineColor = m_color;                    // Default grid color

   

    unsigned int index = 0;

    // Draw vertical lines (XZ plane)
    for (float x = -gridSize; x <= gridSize; x += m_spacing) {
        glm::vec3 color = (fabs(x) == 0) ? xColor : lineColor; // Red if x is near origin
        // Start vertex
        vertices.push_back(glm::vec3(x, 0.0f, -gridSize));  // Position
        vertices.push_back(color);                           // Color
        indices.push_back(index++);

        // End vertex
        vertices.push_back(glm::vec3(x, 0.0f, gridSize));   // Position
        vertices.push_back(color);                           // Color
        indices.push_back(index++);
    }

    // Draw horizontal lines (XZ plane)
    for (float z = -gridSize; z <= gridSize; z += m_spacing) {
        glm::vec3 color = (fabs(z) == 0) ? yColor : lineColor; // Red if z is near origin
        // Start vertex
        vertices.push_back(glm::vec3(-gridSize, 0.0f, z));   // Position
        vertices.push_back(color);                             // Color
        indices.push_back(index++);

        // End vertex
        vertices.push_back(glm::vec3(gridSize, 0.0f, z));      // Position
        vertices.push_back(color);                             // Color
        indices.push_back(index++);
    }

    mVertexIndexBuffer->create(vertices, indices);
};

void ui::Grid::render(Shader& shader, glm::vec3 camPosition) {
    if (!mVertexIndexBuffer) {
        std::cerr << "Error: VertexIndexBuffer not initialized.\n";
        return;
    }

    shader.use();
    shader.SetUniformMat4f("model", glm::mat4(1.0f));
    shader.SetUniform3fv("u_cameraPosition", camPosition);
    //shader.SetUniform3fv("uGridColor", m_color);     

    mVertexIndexBuffer->bind();
    mVertexIndexBuffer->draw(GL_LINES);
    mVertexIndexBuffer->unbind();
};


void ui::Grid::destroy()
{
    mVertexIndexBuffer->destroy();
};