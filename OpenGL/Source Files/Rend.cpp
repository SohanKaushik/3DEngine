
#include <glm/glm.hpp>
#include "Rend.h"
#include "Camera.h"



void Rend::Clear() const {

	// Clear the screen
	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);  //bg color
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};


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
};

void Rend::ModelScale() {
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
};

void Rend::ModelRotate(glm::vec3 axis){
	model = glm::rotate(model, glm::radians(45.0f), axis);
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