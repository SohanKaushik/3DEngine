#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <IndexBuff.h>
#include <VertexBuff.h>
#include <Shader.h>
#include <glm/gtc/matrix_transform.hpp> 

class Rend {
	

private: 

	glm::mat4 proj, view, model;
	double prevTime = 0.0f;
	double currentTime = 0.0f;
	double timeDiff;
	unsigned int counter = 0;


public:

	Rend() {
		proj = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		model = glm::mat4(1.0f);
	};

	void Draw(const VertexBuff& va, const IndexBuff& iv, const Shader& shader) const;
	void Projections(GLFWwindow* window, Shader& shader, const std::string& unformName );
	void Camera(glm::vec3 positions, Shader& shader, const std::string& unformName);

	//Model 
	void ModelTransform(glm::vec3 translation);
	void ModelScale();
	void ModelRotate(glm::vec3 axis);

	void Transform(Shader& shader, const std::string& unformName);
	double FpsCount();
	void Clear() const;
	void Blend();
};
