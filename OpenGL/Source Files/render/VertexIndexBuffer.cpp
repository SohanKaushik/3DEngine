#include "pch.h"
#include "VertexIndexBuffer.h"

using namespace render;

VertexIndexBuffer::VertexIndexBuffer() : m_vertexBuffer(0), m_elementBuffer(0), m_vao(0)
{}



void render::VertexIndexBuffer::create(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices)
{

    // Create and bind VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Create and bind VBO
    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Create and bind EBO
    glGenBuffers(1, &m_elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);



    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)0);
    
    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(3 * sizeof(float)));
    

    // Unbind buffers after use
    glBindVertexArray(0);
};


// Delete the vertex and index buffers
void  VertexIndexBuffer::destroy()
{
    if (m_vertexBuffer) {
        glDeleteBuffers(1, &m_vertexBuffer);
        m_vertexBuffer = 0;
    }
    if (m_elementBuffer) {
        glDeleteBuffers(1, &m_elementBuffer);
        m_elementBuffer = 0;
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    };
};

 // Bind the vertex and index buffers
void VertexIndexBuffer::bind()
{
    glBindVertexArray(m_vao);
};

// Unbind the vertex and index buffers
void VertexIndexBuffer::unbind()
{
    glBindVertexArray(0);
};

// Draw the object using the index buffer
void VertexIndexBuffer::draw(int index_count)
{
    glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
};
