#include "Camera.h"
#include <glm/glm.hpp>
#include <iostream>





Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float near, float far)
    : m_position(position), m_up(up), m_yaw(yaw), m_pitch(pitch),
    m_moveSpeed(10.0f), m_senstivity(0.1f),
    m_fov(fov), m_near(near), m_far(far),
    m_worldUP(glm::vec3(0.0f, 1.0f, 0.0f))
{
	UpdateCameraVectors();
}
 

glm::mat4 Camera::GetProjectionMatrix() {

	return glm::perspective(glm::radians(m_fov), GetAspectRatio(), m_near, m_far);
};



glm::mat4 Camera::GetViewMatrix() const {
	return glm::lookAt(m_position, m_position + m_front, m_up);
};


void Camera::SetAspectRatio(GLFWwindow* window) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	if (height == 0) height = 1;
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

float Camera::GetAspectRatio() {
	return m_aspectRatio;
};


glm::vec3 Camera::GetCameraFront() const {
	// Direction is the vector from camera position to the target
	return m_front;
}


glm::vec3 Camera::GetCameraRight() const {
	// Direction is the vector from camera position to the target
	return m_right;
};


glm::vec3 Camera::GetCameraPosition() const{
	return m_position;
};


void Camera::CalKeyboardMovement(glm::vec3 direction, float deltaTime) {
	float velocity = m_moveSpeed * deltaTime;
	m_position += direction * velocity;    // Move in the specified direction
};

void Camera::CalMouseRotation(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= m_senstivity;
	yOffset *= m_senstivity;

	m_pitch += yOffset;      // Update yaw
	m_yaw += xOffset;        // Update pitch

	// Constrain pitch to avoid gimbal lock
	if (constrainPitch) {
		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;
	}

	// Update camera vectors based on new yaw and pitch
	UpdateCameraVectors();
}
void Camera::UpdateCameraMatrix(Shader& shader)
{
	glm::mat4 view = this->GetViewMatrix();
	glm::mat4 projection = this->GetProjectionMatrix();


	// Set matrices in the shader
	shader.Bind();
	shader.SetUniformMat4f("view", view);
	shader.SetUniformMat4f("projection", projection);
};


void Camera::UpdateCameraVectors() {
	// Ensure the pitch is clamped between -89.0f and 89.0f to avoid gimbal lock
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
};
