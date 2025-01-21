#include "pch.h"
#include "VertexIndexBuffer.h"

using namespace render;

VertexIndexBuffer::VertexIndexBuffer() : m_vbo(0), m_ibo(0), m_vao(0)
{}



void render::VertexIndexBuffer::create(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices)
{
    if (vertices.empty()) {
        std::cerr << "Error: [Vertices are empty]" << std::endl;
        return;
    }
    if (indices.empty()) {
        std::cerr << "Error: [Indices are empty]" << std::endl;
        return;
    }

    // Create and bind VAO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // Create and bind VBO
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    // Create and bind EBO
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);



    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)0);
    
    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)(3 * sizeof(float)));
    

    // Unbind buffers after use
    glBindVertexArray(0);

    m_indices = indices.size();
};


void render::VertexIndexBuffer::create(const std::vector<VertexHolder>& vertices, const std::vector<unsigned int>& indices)
{
    if (vertices.empty()) {
        std::cerr << "Error : [VertexHolder is Empty]" << std::endl;
        return;
    } 
    
    if (indices.empty()) {
        std::cerr << "Error : [Indices are Empty]" << std::endl;
        return;
    }

    // OpenGL buffer setup
    glGenVertexArrays(1, &m_vao);

    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ibo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexHolder), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Define VertexHolder attributes based on the VertexHolder struct
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexHolder), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexHolder), (void*)offsetof(VertexHolder, normal));

   /* glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexHolder), (void*)offsetof(VertexHolder, texCoords));*/

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_indices = indices.size();
};


// Delete the VertexHolder and index buffers
void VertexIndexBuffer::destroy()
{
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_ibo) {
        glDeleteBuffers(1, &m_ibo);
        m_ibo = 0;
    }
}


// Bind the VertexHolder and index buffers
void VertexIndexBuffer::bind()
{
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
};

// Unbind the VertexHolder and index buffers
void VertexIndexBuffer::unbind()
{       
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

// Draw the object using the index buffer
void VertexIndexBuffer::draw(GLenum mode)
{
    if (m_indices == 0) {
        std::cerr << "Warning: No indices to draw." << std::endl;
        return;
    }

    glDrawElements(mode, m_indices, GL_UNSIGNED_INT, nullptr);
};
