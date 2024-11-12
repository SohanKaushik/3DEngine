
#include <glm/glm.hpp>
#include "Rend.h"




void Rend::Clear() const {

	// Clear the screen
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  //bg color

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);
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


void Rend::Projections(GLFWwindow* window, Shader& shader, const std::string& unformName) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);


	if (height == 0) height = 1;
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	//proj = glm::ortho(-aspectRatio , aspectRatio, 1.0f, -1.0f);
	proj = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 1000.0f);
	shader.SetUniformMat4f(unformName, proj);
};


//Warning: Use a Model Matrix to move objects.The View matrix only moves the camera.	
void Rend::Camera(glm::vec3 positions , Shader& shader, const std::string& unformName) {
	view = glm::translate(glm::mat4(1.0), positions);
	glm::mat4 mvp = proj * view;
	shader.SetUniformMat4f(unformName, mvp);
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


void Rend::Transform(Shader& shader, const std::string& unformName) {
	glm::mat4 mvp = proj * view * model;
	shader.SetUniformMat4f(unformName, mvp);
};

double Rend::FpsCount() {
	currentTime = glfwGetTime();
	timeDiff = currentTime - prevTime;
	counter++;


	if (timeDiff >= 1.0 / 30.0) {
		return (1.0 / timeDiff) * counter;
	}

	prevTime = currentTime;
	counter = 0;
};