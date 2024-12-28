#include "pch.h"

#include "Camera.h"


elems::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float nearDis, float farDis)
	: m_position(position), m_up(up), m_yaw(yaw), m_pitch(pitch),
	m_moveSpeed(10.0f), m_senstivity(0.1f),
	m_fov(fov), m_near(nearDis), m_far(farDis)
{
	//UpdateCameraVectors();
	
}
elems::Camera::Camera(ProjectionType type, float fov, float nearDis, float farDis)
	: m_fov(fov), m_near(nearDis), m_far(farDis), m_projection(type)
{};


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
	m_position = position;
	m_targetPos = target_pos;
	m_view = glm::lookAt(m_position, m_targetPos, m_up);
};

glm::mat4 elems::Camera::GetViewMatrix() const
{
	return m_view;
};


void elems::Camera::set_aspect(float size) {
	m_aspectRatio = size;
	/*int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	if (height == 0) height = 1;
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);*/
};

float  elems::Camera::GetAspectRatio() {
	return m_aspectRatio;
};

glm::vec3 elems::Camera::GetCameraFront() const {
	// Direction is the vector from camera position to the target
	return m_front;
};

glm::vec3 elems::Camera::GetCameraRight() const {
	// Direction is the vector from camera position to the target
	return m_right;
};


glm::vec3  elems::Camera::GetCameraPosition() const {
	return m_position;
};


void  elems::Camera::UpdateCameraMatrix(Shader& shader)
{
	glm::mat4 view = this->GetViewMatrix();
	glm::mat4 projection = this->GetProjectionMatrix();
	// Set matrices in the shader
	shader.use();
	shader.SetUniformMat4f("view", view);
	shader.SetUniformMat4f("projection", projection);
};

void elems::Camera::UpdateCameraVectors() {

	//// Ensure the pitch is clamped between -89.0f and 89.0f to avoid gimbal lock
	if (m_pitch > 89.0f) m_pitch = 89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	// Calculate the new front vector based on yaw and pitch
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_front = glm::normalize(front); // Normalize front vector


	m_right = glm::normalize(glm::cross(m_front, m_worldUP));   // Right is the cross product of front and world up
	m_up = glm::normalize(glm::cross(m_right, m_front));        // Up is the cross product of right and front

	/*std::cout << "Front: " << glm::to_string(m_front) << "\n";
	std::cout << "Right: " << glm::to_string(m_right) << "\n";
	std::cout << "Up: " << glm::to_string(m_up) << "\n";*/


};


float elems::Camera::GetDistance() {

	return glm::length(m_position - m_targetPos);
}