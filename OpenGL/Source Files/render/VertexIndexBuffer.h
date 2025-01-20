#pragma once
#include <pch.cpp>
#include "vertex_holder.h"

namespace render {

	class VertexIndexBuffer {

	public:
		VertexIndexBuffer();


		// Create buffers with vertices and indices
		void create(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices);
		void create(const std::vector<VertexHolder>& vertices, const std::vector<unsigned int>& indices);

		// Destroy buffers
		void destroy();

		// Bind the VertexHolder array (VAO)
		void bind();

		// Unbind the VertexHolder array (VAO)
		void unbind();

		// Draw the object using the index buffer
		void draw(GLenum mode);
		
	private:
		unsigned int m_vao = 0;  // VertexHolder array object
		unsigned int m_vbo = 0;  // VertexHolder buffer object
		unsigned int m_ibo = 0;  // ebo(index buffer object)

	private:
		
		 int m_indices = 0;
	};
}