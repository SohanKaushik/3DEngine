#pragma once


#include <glm/gtc/matrix_transform.hpp> 
#include <string>
#include <GLFW/glfw3.h>



class Camera {
		
private:
	glm::vec3 m_positions;

	float m_fov;
	float m_near;
	float m_far;
	GLFWwindow* m_window;


public:
	Camera(glm::vec3 position, float fov, float near, float far, GLFWwindow* window);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();
	float GetAspectRatio();
};						