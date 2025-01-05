#pragma once
#include "pch.h"

#include "shader/shader.h"
#include "render/camera_uniforms.h"
#include "render/framebuffer.h"

namespace elems {

	enum class ProjectionType { Orthographic, Perspective };

	struct CameraUniforms {
		glm::mat4 view;
		glm::mat4 proj;
		glm::vec3 pos;
		glm::vec3 rot;
		float padding; // Ensure 16-byte alignment if needed
	};

	class Camera {

	private:
		
		ProjectionType m_projection;

		glm::vec3 m_targetPos = glm::vec3(0.0f, 0.0f, 0.0f);  // Camera looks at the origin

		glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);         // World up direction
		glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);     // Default forward direction
		glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);      // Default right direction
		glm::vec3 m_worldUP = glm::vec3(0.0f, 1.0f, 0.0f);    // Explicitly set world up
		glm::vec3 m_position = glm::vec3(0.0f, 0.0f, -1.0f);  // Camera starts at (0, 0, -1)

		bool isActive;

		float m_fov;
		float m_near;
		float m_far;

	public:
		CameraUniforms mCameraUniforms;
		Camera() = default;

		// Perspective Projection
		Camera(ProjectionType type, float fov, float clip_start, float clip_end);

		//Orthographic Projection
		//Camera(float aspect, float fov, float nearDis, float farDis);

		glm::vec3 GetCameraPosition() const;
		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix() const;

		void SetViewMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 target_pos);
		void UpdateCameraMatrix(Shader& shader);

		
	private:
		//std::unique_ptr<render::CameraUniforms> mCmaeraUniforms; 
		//std::unique_ptr<render::CameraUniformFrameBuffer> mCameraFrameBuffer; 
	};

}