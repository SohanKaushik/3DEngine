#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <IndexBuff.h>
#include <VertexBuff.h>
#include "shader/shader.h"
#include <glm/gtc/matrix_transform.hpp> 

#include "elems/camera.h"
using namespace elems;

class Rend {
	
public:
	 Rend(Camera& cam);

private: 

	
	double prevTime = 0.0f;
	double currentTime = 0.0f;
	double timeDiff;
	unsigned int counter = 0;

	glm::mat4 proj, view, model = glm::mat4(1.0f);
	glm::vec3 m_modelPosition = glm::vec3(0,0,0);
	glm::mat4 m_modelRotate = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 m_modelScale = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

	Camera m_camera;

public:
	


	void Draw(const VertexBuff& va, const IndexBuff& iv, const Shader& shader) const;
	

	//Model 
	void SetModelPosition(glm::vec3 translation);
	void SetModelScale();                                       
	void SetModelRotate(glm::vec3 axis, float radian);
	void SetModelColor(glm::vec3 color, const std::string& uniformName, Shader& shader);

	void UpdateMatrix(Shader& shader, const std::vector <std::string>& uniformName, Camera& cam);
	double FpsCount();
	void Clear() const;
	void Blend();


private:
	unsigned int gridVAO, gridVBO;

public:
	glm::mat4 GetModelMatrix();
	glm::vec3 GetModelPosition();


	void SetupGrid();
	void DrawGrid(float spacing, float thickness, const glm::vec3& gridColor, const glm::vec3& bgColor, Shader& gridShader, Camera& camera) const;
}; 
