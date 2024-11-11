#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <IndexBuff.h>
#include <VertexBuff.h>
#include <Shader.h>

class Rend {
	

private: 
	glm::mat4 proj, view;

public:
	void Draw(const VertexBuff& va, const IndexBuff& iv, const Shader& shader) const;
	void UpdadeProjections(GLFWwindow* window, Shader& shader, const std::string& unformName);
	void Camera(float x, float y, float z, Shader& shader, const std::string& unformName);
	void Transform(float x, float y, float  z, Shader& shader, const std::string& unformName);
	void Clear() const;
	void Blend();
};
