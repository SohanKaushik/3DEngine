#pragma once
#include "pch.h"
#include "render/VertexIndexBuffer.h"

namespace elems {

	class Primitive {

	public:

		void plane();
		void cube();
		void sphere();

		const std::vector<glm::vec3>& getVertices() const;
		const std::vector<VertexHolder>& get_vertx() const;
		const std::vector<unsigned int> get_indices() const;

	private:
		std::unique_ptr<render::VertexIndexBuffer> m_buffer = std::make_unique<render::VertexIndexBuffer>();
		std::vector<glm::vec3> m_verticesz;       // VertexHolder data (positions, normals, etc.).
		std::vector<unsigned int> m_indices;        

		std::vector<VertexHolder> m_vertices;
	};
}