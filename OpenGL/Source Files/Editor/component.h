#pragma once
#include "pch.h"
#include "elems/mesh.h"
#include "Editor/EditorCamera.h"
#include "thread"
#include "future"

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <elems/light/light.h>
#include <elems/materia.h>

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

	class MeshComponent : public Component {
	private: 
		std::unique_ptr<elems::Mesh> mesh; 

	public:
		MeshComponent() {
			mesh = std::make_unique<elems::Mesh>();  // this just makes an container and not actually output any mesh
			//shader = std::make_shared<elems::Shader>("path/to/shader.vert", "path/to/shader.frag");  // Load shader (path is an example)
		}

		void SetMesh(const elems::PrimitiveType& primitive) {
			mesh = std::make_unique<elems::Mesh>(primitive);
		}

		
		void load(const std::string& path) {
			mesh->load(path);
		}

		auto GetMesh() { 
			return mesh.get(); 
		}

		auto GetShader() {

		}
	};


	class MaterialComponent : public Component{
	private:
		std::unique_ptr<elems::IMaterial> material;
	public:
		MaterialComponent() {
			material = std::make_unique<elems::Material<elems::Lambert>>();
		}

		template<typename ShaderModel>
		void AddMaterial() {
			material = std::make_unique<elems::Material<ShaderModel>>();
		}

		auto* GetMaterial() const {
			assert(material && "MaterialComponent has no material!");
			return material.get();
		}

		Shader& GetShader(){
			assert(material && "MaterialComponent has no material!");
			return material->GetShader();
		}
	};


	class LightComponent : public Component {
	private:
		elems::LightParams params;
		std::unique_ptr<elems::Light> light;

	public:
		LightComponent() = default;



		void SetDirectionalLight() {
			light = std::make_unique<elems::DirectionalLight>(&params);
		}

		void SetPointLight() {
			//light = std::make_unique<elems::PointLight>(ldata);
		}

		void SetSpotLight() {
			//light = std::make_unique<elems::SpotLight>(ldata);
		}


		auto& GetLightData() { return params; }
		auto* GetLight() {return light.get();}
	};

};