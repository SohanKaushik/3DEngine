
#include <glm/glm.hpp>
#include "Rend.h"



void Rend::Clear() const {

	// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  //bg color
	glClear(GL_COLOR_BUFFER_BIT);

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


void Rend::UpdadeProjections(GLFWwindow* window, Shader& shader, const std::string& unformName) {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);


	if (height == 0) height = 1;
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	proj = glm::ortho(-aspectRatio , aspectRatio, 1.0f, -1.0f);
	shader.SetUniformMat4f(unformName, proj);
};


//Warning: Use a Model Matrix to move objects.The View matrix only moves the camera.	

void Rend::Camera(float x, float y, float  z, Shader& shader, const std::string& unformName) {
	view = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));
	glm::mat4 mvp = proj * view;
	shader.SetUniformMat4f(unformName, mvp);
};


// Model Matrix
void Rend::Transform(glm::vec3 translation, Shader& shader, const std::string& unformName) {
	glm::mat4 model = glm::translate(glm::mat4(1.0), translation);
	glm::mat4 mvp = proj * view * model;
	shader.SetUniformMat4f(unformName, mvp);
};