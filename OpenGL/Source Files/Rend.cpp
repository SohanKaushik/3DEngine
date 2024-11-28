
#include <glm/glm.hpp>
#include "Rend.h"
#include "Camera.h"
#include "window.h"

void Rend::Clear() const {
	// Set the background color
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Rend::Blend() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Rend::Draw(const VertexBuff& va, const IndexBuff& iv, const Shader& shader) const {

	shader.Bind();
	iv.Bind();
	va.Bind();
	glDrawElements(GL_TRIANGLES, iv.GetCount() , GL_UNSIGNED_INT, 0);
};


// Model Matrix
void Rend::ModelTransform(glm::vec3 translation) {
	model = glm::translate(glm::mat4(1.0), translation);
	m_modelPosition = translation;
};

void Rend::ModelScale() {
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
};

void Rend::ModelRotate(glm::vec3 axis, float radian){
	model = glm::rotate(model, glm::radians(radian), axis);
};


// All Matrix Transform
void Rend::UpdateMatrix(Shader& shader, const std::string& unformName, Camera& cam) {
	glm::mat4 mvp = cam.GetProjectionMatrix() * cam.GetViewMatrix() * model;

	// Debug: print out the MVP matrix
	shader.SetUniformMat4f(unformName, mvp);
};

double Rend::FpsCount() {
	currentTime = glfwGetTime();
	timeDiff = currentTime - prevTime;
	counter++;


	if (timeDiff >= 1.0 / 30.0) {
		double fps = (1.0 / timeDiff) * counter;
		return fps;
	}

	prevTime = currentTime;
	counter = 0;

	return NULL;
};


glm::mat4 Rend:: GetModelMatrix() {
	return model;
};

glm::vec3 Rend::GetModelPosition() {
	return m_modelPosition;
};

void Rend::DrawGrid(float spacing, float thickness, const glm::vec3& gridColor, const glm::vec3& bgColor, Shader& gridShader) const
{
	//Window winowSize;
	gridShader.Bind();
	//gridShader.SetUniform2f("viewportSize",);
	gridShader.SetUniform1f("spacing", spacing);

	//glBindVertexArray(gridVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
};