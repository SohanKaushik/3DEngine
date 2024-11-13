#include "Camera.h"
#include <glm/glm.hpp>





Camera :: Camera(glm::vec3 position, float fov, float near, float far, GLFWwindow* window)
	: m_positions(position), m_fov(fov), m_near(near), m_far(far), m_window(window)
{}
 

glm::mat4 Camera::GetProjectionMatrix() {

	return glm::perspective(glm::radians(m_fov), GetAspectRatio(), m_near, m_far);
};



glm::mat4 Camera::GetViewMatrix() {
	return glm::lookAt(
				glm::vec3(0.0f, 0.0f, 3.0f),
				glm::vec3(0.0f, 0.0f, -1.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));
};


float Camera::GetAspectRatio() {

	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);

	if (height == 0) height = 1;
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	return aspectRatio;
};

