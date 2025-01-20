#pragma once
#include "pch.h"
#include "elems/mesh.h"
#include "Editor/EditorCamera.h"
#include "thread"
#include "future"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

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

		struct Transform {
			glm::vec3 position = glm::vec3(0.0f);
			glm::vec3 rotation = glm::vec3(0.0f);
			glm::vec3 scale = glm::vec3(1.0f);
		} m_transform;

	public:

		TransformComponent() = default;
		
		void SetPosition(const glm::vec3& pos) {
			m_transform.position = pos;
		}

		void SetRotation(const glm::vec3& rot) {
			m_transform.rotation = rot;
		}

		void SetScale(const glm::vec3& scal) {
			m_transform.scale = scal;
		}

		auto& GetPosition() {
			return m_transform.position;
		}

		auto& GetRotation() {
			return m_transform.rotation;
		}

		auto& GetScale() {
			return m_transform.scale;
		}

		glm::mat4 GetModelUniforms() {

			// position
			m_model = glm::translate(glm::mat4(1.0f), m_transform.position);

			// rotation
			glm::mat4 rot_matrix = glm::mat4(1.0f);
			rot_matrix = glm::rotate(rot_matrix, glm::radians(m_transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
			rot_matrix = glm::rotate(rot_matrix, glm::radians(m_transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
			rot_matrix = glm::rotate(rot_matrix, glm::radians(m_transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
			m_model = m_model * rot_matrix;

			// scale
			m_model = glm::scale(m_model, m_transform.scale);

			return m_model;
		}

	private:
		glm::mat4 m_model = glm::mat4(1.0f);
	};

	class MeshComponent : public Component {
	private: 
		std::unique_ptr<elems::Mesh> mesh; 
		glm::vec3 m_color;

	public:
		MeshComponent() {
			//mesh = std::make_unique<elems::Mesh>(elems::PrimitiveType::cube);  
			m_color = glm::vec3(1.0f);
			//shader = std::make_shared<elems::Shader>("path/to/shader.vert", "path/to/shader.frag");  // Load shader (path is an example)
		}

		void SetMesh(const elems::PrimitiveType& primitive) {
			mesh = std::make_unique<elems::Mesh>(primitive);
		}

		
		void load(const std::string& path) {
			mesh->load(path);
		}
		
		void SetMaterial(const glm::vec3& color) {
			m_color = color;
		}

		auto& GetColor() {
			return m_color;
		}

		auto GetMesh() { 
			return mesh.get(); 
		}

		auto GetShader() {

		}
	};


	class CameraComponent {
	public:
		CameraComponent() = default;

		std::shared_ptr<Camera> GetCamera() const {
			return m_camera;
		}

	private:
		std::shared_ptr<Editor::Camera> m_camera;  
	};

};