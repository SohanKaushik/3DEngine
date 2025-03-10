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

	class Components {

	public:
		virtual ~Components() = default;
	};

	class TagComponent : Components {
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

	class TransformComponent : public Components {

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

			/* Euler Rotation*/ 

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

	class MeshComponent : public Components {
	private: 
		std::unique_ptr<elems::Mesh> mesh; 
		glm::vec3 m_color;

	public:
		MeshComponent() {
			mesh = std::make_unique<elems::Mesh>();  // this just makes an container and not actually output any mesh
			m_color = glm::vec3(1.0f);
			//shader = std::make_shared<elems::Shader>("path/to/shader.vert", "path/to/shader.frag");  // Load shader (path is an example)
		}

		void SetMesh(const elems::primvtype& primitive) {
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

	};

	class MaterialComponent : public Components {

	public:
		enum class ModelType { Phong, Lambertian, PBR };

	private:
		glm::vec3 m_color{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_ambient{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_diffuse{ 1.0f, 1.0f, 1.0f };
		glm::vec3 m_specular{ 0.5f, 0.5f, 0.5f };
		float m_shininess{ 32.0f }; // Higher = shinier
		float m_alpha = 1.0f;

	private:
		Shader _shader;

	public:
		MaterialComponent() {
			_shader.load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
		}

	public:
		void SetAmbient(const glm::vec3& amb) { m_ambient = amb; }
		void SetDiffuse(const glm::vec3& diff) { m_diffuse = diff; }
		void SetSpecular(const glm::vec3& spec) { m_specular = spec; }
		void SetShininess(float shin) { m_shininess = shin; }
		void SetAlpha(float alpha) { m_alpha = alpha; }

		auto& GetColor() { return m_color; }
		const glm::vec3& GetAmbient() const { return m_ambient; }
		const glm::vec3& GetDiffuse() const { return m_diffuse; }
		const glm::vec3& GetSpecular() const { return m_specular; }
		float GetShininess() const { return m_shininess; }
		float& GetAlpha() { return m_alpha; }


		auto GetShader() {
			return _shader;
		}

		void SetShader(ModelType type) {
			switch (type) {
			case ModelType::Phong:
				_shader.load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
				break;

				case ModelType::Lambertian:
					_shader.load("Resource Files/Shaders/shadingmodels/phong.vert", "Resource Files/Shaders/shadingmodels/phong.frag");
					break;
				/*
				case ModelType::PBR:
					_shader.load("Resource Files/Shaders/pbr.vert", "Resource Files/Shaders/pbr.frag");
					break;*/
			}
		}
	};

};