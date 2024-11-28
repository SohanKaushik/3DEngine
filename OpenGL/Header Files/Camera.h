#pragma once


#include <glm/gtc/matrix_transform.hpp> 
#include <string>
#include <GLFW/glfw3.h>



class Camera {
		
private:
	glm::vec3 m_position = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_targetPos = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_front;
	glm::vec3 m_right;
	glm::vec3 m_worldUP;


	float m_fov;
	float m_near;
	float m_far;

	float m_aspectRatio;
	//GLFWwindow* m_window;

private:
	float m_yaw;
	float m_pitch;

	float m_moveSpeed;
	float m_senstivity;

public:
	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float fov, float near, float far);

	glm::vec3 GetCameraPosition();
	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix() const;
	glm::vec3 GetCameraFront() const;
	glm::vec3 GetCameraRight() const;
	void SetAspectRatio(GLFWwindow* window);
	float GetAspectRatio();
	

	void CalKeyboardMovement(glm::vec3 direction, float deltaTime);
	void CalMouseRotation(float xOffset, float yOffset, bool contrainPitch);

private:
	void UpdateCameraVectors();

};						