#pragma once
#include <pch.cpp>

namespace render {

	class VertexIndexBuffer {

	public:
		VertexIndexBuffer();


		// Create buffers with vertices and indices
		void create(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices);

		// Destroy buffers
		void destroy();

		// Bind the vertex array (VAO)
		void bind();

		// Unbind the vertex array (VAO)
		void unbind();

		// Draw the object using the index buffer
		void draw(int index_count);
		
	private:
		unsigned int m_vao = 0;  // Vertex buffer ID
		unsigned int m_vertexBuffer = 0;   // Index buffer ID
		unsigned int m_elementBuffer = 0;

	private:
		unsigned int m_indices = 0;
	};

	

}