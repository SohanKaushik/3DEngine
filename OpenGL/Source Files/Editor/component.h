#pragma once
#include "pch.h"
#include "elems/mesh.h"

namespace Editor {

	class Component {

	public:
		virtual ~Component() = default;
	};

	class TagComponent : Component {
	private:
		std::string m_tag;

		TagComponent() = default;

	public:
		void SetTag(const std::string& tag) {
			m_tag = tag;
		}
		auto GetTag() {
			return m_tag;
		}
	};

	class TransformComponent : public Component {
	public:
		struct Transform {
			glm::vec3 position = glm::vec3(0.0f);
			glm::vec3 rotation = glm::vec3(0.0f);
			glm::vec3 scale = glm::vec3(1.0f);
		} m_transform;

		TransformComponent() = default;
		
		void SetPosition(const glm::vec3& pos) {
			m_transform.position = pos;
			m_model = glm::translate(glm::mat4(1.0f), m_transform.position);
		}

		void SetRotation(const glm::vec3& rot) {
			m_transform.rotation = rot;
		}

		void SetScale(const glm::vec3& scal) {
			m_transform.scale = scal;
			m_model = glm::scale(glm::mat4(1.0f), m_transform.scale);
		}

		auto& GetPosition() {
			m_model = glm::translate(glm::mat4(1.0f), m_transform.position);
			return m_transform.position;
		}

		auto& GetRotation() {
			//m_model = glm::translate(glm::mat4(1.0f), m_transform.position);
			return m_transform.rotation;
		}

		auto& GetScale() {
			m_model = glm::scale(glm::mat4(1.0f), m_transform.scale);
			return m_transform.scale;
		}

		glm::mat4 GetModelUniforms() {
			return m_model;
		}

	private:
		glm::mat4 m_model = glm::mat4(1.0f);
	};

	class MeshComponent : public Component {
	private: 
		std::unique_ptr<elems::Mesh> mesh; 
	public:
		MeshComponent() {
			mesh = std::make_unique<elems::Mesh>(elems::PrimitiveType::cube);   
			//shader = std::make_shared<elems::Shader>("path/to/shader.vert", "path/to/shader.frag");  // Load shader (path is an example)
		}

		void SetMesh(const elems::PrimitiveType& primitive) {
			mesh = std::make_unique<elems::Mesh>(primitive);
		}

		auto GetMesh() { 
			return mesh.get(); 
		}

		auto GetShader() {

		}
	};
};