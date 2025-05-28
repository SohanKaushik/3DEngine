#include "pch.h"

#include "elems/camera.h"


elems::Camera::Camera(ProjectionType type, float fov, float nearDis, float farDis)
	: m_fov(fov), m_near(nearDis), m_far(farDis), m_projection(type)
{
	//mCameraFrameBuffer->create_buffer(mCameraUniforms);
};


glm::mat4 elems::Camera::GetProjectionMatrix() {

	switch (m_projection)
	{
	case ProjectionType::Orthographic: 
		std::cout << "Orthographic not available!!" << std::endl;
		break;

	case ProjectionType::Perspective: 
		return glm::perspective(glm::radians(m_fov), 1.0f, m_near, m_far);

	default:
		break;
	};
};


void elems::Camera::SetViewMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 target_pos) {
	//return glm::lookAt(m_position, m_position + m_front, m_up);
	m_targetPos = target_pos;
	mCameraUniforms.pos = position;
	mCameraUniforms.view = glm::lookAt(m_position, m_targetPos, m_up);
};

glm::mat4 elems::Camera::GetViewMatrix() const
{
	return mCameraUniforms.view;
};
	
glm::vec3  elems::Camera::GetCameraPosition() const {
	return mCameraUniforms.pos;
};


//void  elems::Camera::UpdateCameraMatrix(Shader& shader)
//{
//	mCameraUniforms.view = this->GetViewMatrix();
//	mCameraUniforms.proj = this->GetProjectionMatrix();
//	
//	// Update the Uniforms
//	mCameraFrameBuffer->update_buffer(mCameraUniforms);
//	mCameraFrameBuffer->bind();
//
//	shader.SetUniformMat4f("view", mCameraUniforms.view);
//	shader.SetUniformMat4f("projection", mCameraUniforms.proj);
//};
