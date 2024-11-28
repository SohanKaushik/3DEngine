#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <IndexBuff.h>
#include <VertexBuff.h>
#include <Shader.h>
#include <glm/gtc/matrix_transform.hpp> 

#include "Camera.h"

class Rend {
	

private: 

	glm::mat4 proj, view, model;
	double prevTime = 0.0f;
	double currentTime = 0.0f;
	double timeDiff;
	unsigned int counter = 0;
	
	glm::vec3 m_modelPosition;

public:


	void Draw(const VertexBuff& va, const IndexBuff& iv, const Shader& shader) const;
	

	//Model 
	void ModelTransform(glm::vec3 translation);
	void ModelScale();                                       
	void ModelRotate(glm::vec3 axis, float radian);

	void UpdateMatrix(Shader& shader, const std::string& uniformName, Camera& cam);
	double FpsCount();
	void Clear() const;
	void Blend();


public:
	glm::mat4 GetModelMatrix();
	glm::vec3 GetModelPosition();

	void DrawGrid(float spacing, float thickness, const glm::vec3& gridColor, const glm::vec3& bgColor, Shader& shader) const;
};
