#include "pch.h"

#include "Camera.h"


elems::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float nearDis, float farDis)
	: m_position(position), m_up(up), m_yaw(yaw), m_pitch(pitch),
	m_moveSpeed(10.0f), m_senstivity(0.1f),
	m_fov(fov), m_near(nearDis), m_far(farDis)
{
	//UpdateCameraVectors();
	
};


glm::mat4 elems::Camera::GetProjectionMatrix() {

	return glm::perspective(glm::radians(m_fov), this->GetAspectRatio(), m_near, m_far);
};


glm::mat4  elems::Camera::GetViewMatrix() const {
	//return glm::lookAt(m_position, m_position + m_front, m_up);
	return glm::lookAt(m_position, m_targetPos, m_up);
};


void elems::Camera::set_aspect(float size) {
	m_aspectRatio = size;
	/*int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	if (height == 0) height = 1;
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);*/
}

float  elems::Camera::GetAspectRatio() {
	return m_aspectRatio;
};


glm::vec3 elems::Camera::GetCameraFront() const {
	// Direction is the vector from camera position to the target
	return m_front;
}


glm::vec3 elems::Camera::GetCameraRight() const {
	// Direction is the vector from camera position to the target
	return m_right;
};


glm::vec3  elems::Camera::GetCameraPosition() const {
	return m_position;
};


void  elems::Camera::CalKeyboardMovement(glm::vec3 direction, float deltaTime) {
	float velocity = m_moveSpeed * deltaTime;
	m_position += direction * velocity;    // Move in the specified direction
};

void elems::Camera::on_mouse_move(float deltaYaw, float deltaPitch, bool constrainPitch) {
	m_yaw += deltaYaw;    // Rotate horizontally (yaw)
	m_pitch += deltaPitch; // Rotate vertically (pitch)

	// Constrain pitch to avoid gimbal lock (this can be removed for unrestricted pitch rotation)
	if (constrainPitch) {
		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;
	}

	// Normalize yaw to ensure it stays within the 0 - 360 degree range
	if (m_yaw > 360.0f) {
		m_yaw -= 360.0f;
	}

	UpdateOrbit();  // Update camera position and orientation
	// Fix Gimble Lock 
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

void elems::Camera::UpdateOrbit() {
	// Spherical to Cartesian conversion
	float radius = glm::length(m_position - m_targetPos);  // Distance to the target

	glm::vec3 offset;
	offset.x = radius * cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	offset.y = radius * sin(glm::radians(m_pitch));
	offset.z = radius * cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));

	// Update camera position
	m_position = m_targetPos + offset;

	// Update camera orientation vectors
	m_front = glm::normalize(m_targetPos - m_position); // Look direction
	m_right = glm::normalize(glm::cross(m_front, m_worldUP)); // Right direction
	m_up = glm::normalize(glm::cross(m_right, m_front)); // Up direction
};

void elems::Camera::UpdateZoom(float offset, Shader& shader) {
	glm::vec3 forward = glm::normalize(m_targetPos - m_position);

	// Move the camera closer/farther from the target
	m_position += forward * offset;

	// Clamp the zoom distance
	float distance = glm::length(m_targetPos - m_position);
	if (distance < m_near) {
		m_position = m_targetPos - forward * m_near;
	}
	else if (distance > m_far) {
		m_position = m_targetPos - forward * m_far;
	}

	this->UpdateCameraMatrix(shader);
};


float elems::Camera::GetDistance() {

	return glm::length(m_position - m_targetPos);
}