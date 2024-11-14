#include "Camera.h"
#include <glm/glm.hpp>





Camera :: Camera(glm::vec3 position, float fov, float near, float far, GLFWwindow* window)
	: m_position(position), m_fov(fov), m_near(near), m_far(far), m_window(window)
{}
 

glm::mat4 Camera::GetProjectionMatrix() {

	return glm::perspective(glm::radians(m_fov), GetAspectRatio(), m_near, m_far);
};



glm::mat4 Camera::GetViewMatrix() {

	m_targetPos = glm::vec3(0.0f, 0.0f, 0.0f);  // Example: looking at the origin
	glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);     // orientation ( z up )

	return glm::lookAt(m_position,m_targetPos,upDirection); 
};


float Camera::GetAspectRatio() {

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	if (height == 0) height = 1;
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	return aspectRatio;
};


glm::vec3 Camera::GetCameraFront() {
	// Direction is the vector from camera position to the target
	return glm::normalize(m_targetPos - m_position);
}


glm::vec3 Camera::GetCameraPosition() {
	return m_position;
};

