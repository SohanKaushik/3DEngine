#pragma once
#include "pch.h"
#include "render/VertexIndexBuffer.h"

namespace elems {


	enum class ShapeType {
		Plane,
		Cube,
		Sphere,
		// Add other shapes here.
	};


	class Primitive {

	public:

		Primitive(const std::string& id);
		void render();
		void gen_cube();
		void load_from_file();

	private:
		std::unique_ptr<render::VertexIndexBuffer> m_buffer = std::make_unique<render::VertexIndexBuffer>();
		std::vector<glm::vec3> m_vertices;       // Vertex data (positions, normals, etc.).
		std::vector<uint32_t> m_indices;         // Index data.

	private:
		std::string m_id; // Unique identifier
	};
}