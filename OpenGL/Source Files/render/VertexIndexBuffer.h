#pragma once
#include <pch.cpp>

namespace Render {

	class VertexIndexBuffer {

	public:
		VertexIndexBuffer();


		void create(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices);
		void destroy();
		void bind();
		void unbind();
		void draw(int index_count);
		void print();

	private:
		unsigned int m_vertexBuffer = 0;  // Vertex buffer ID
		unsigned int m_indexBuffer;   // Index buffer ID
	};

	

}