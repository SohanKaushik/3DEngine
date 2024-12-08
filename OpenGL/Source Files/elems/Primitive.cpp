#include "pch.h"
#include "Primitive.h"

elems::Primitive::Primitive(const std::string& id)
{
    gen_cube();
    m_buffer->create(m_vertices, m_indices);
};

void elems::Primitive::render()
{
    m_buffer->bind();
    m_buffer->draw(m_indices.size());

};

void elems::Primitive::gen_cube()
{
    m_vertices = {
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

    m_indices = {
        0, 1, 2,  2, 3, 0,  // Front face
        4, 5, 6,  6, 7, 4,  // Back face
        8, 9, 10,  10, 11, 8, // Left face
        12, 13, 14,  14, 15, 12, // Right face
        16, 17, 18,  18, 19, 16, // Top face
        20, 21, 22,  22, 23, 20  // Bottom face
    };


};




