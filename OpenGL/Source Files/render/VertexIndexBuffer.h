#pragma once
#include <pch.cpp>

namespace Render {

	class VertexIndexBuffer {

	public:
		VertexIndexBuffer();

		void create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
		void remove();
		void bind();
		void unbind();
		void draw(int index_count);

	private:
		unsigned int m_vertexBuffer;  // Vertex buffer ID
		unsigned int m_indexBuffer;   // Index buffer ID
	};

}