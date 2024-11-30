
#include <glm/glm.hpp>
#include "Rend.h"
#include "Camera.h"
#include "window.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>



Rend::Rend(Camera& cam) : m_camera(cam)
{};


void Rend::Clear() const {
	// Set the background color
	glClearColor(0.247, 0.247, 0.247, 1.0);

	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Rend::Blend() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};


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
    glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(radian), axis);
};


// All Matrix Transform
void Rend::UpdateMatrix(Shader& shader, const std::string& unformName, Camera& camera) {
	glm::mat4 mvp = camera.GetProjectionMatrix() * camera.GetViewMatrix() * model;

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





void Rend::DrawGrid(float spacing, float thickness, const glm::vec3& gridColor, const glm::vec3& bgColor, Shader& gridShader, Camera& camera) const
{


    // Set grid shader uniforms
    gridShader.Bind();
    gridShader.SetUniform3fv("u_gridColor", gridColor);
    gridShader.SetUniform3fv("u_cameraPosition", camera.GetCameraPosition());
    gridShader.SetUniformMat4f("u_model", model);
    
    // Create grid lines data (just an example of a 2D grid in XZ plane)
    std::vector<float> gridVertices;

   
    // Draw vertical lines (XZ plane)
    for (float x = -1000.0f; x <= 1000.0f; x += spacing) {

        if (x == 1000) {
            std::cout << "x yes" << std::endl;
        }
        gridVertices.push_back(x); gridVertices.push_back(0.0f); gridVertices.push_back(-1000.0f);  // Start
        gridVertices.push_back(x); gridVertices.push_back(0.0f); gridVertices.push_back(1000.0f);   // End
    }

    // Draw horizontal lines (XZ plane)
    for (float z = -1000.0f; z <= 1000.0f; z += spacing) {
        gridVertices.push_back(-1000.0f); gridVertices.push_back(0.0f); gridVertices.push_back(z);  // Start
        gridVertices.push_back(1000.0f); gridVertices.push_back(0.0f); gridVertices.push_back(z);   // End
    }

    // Bind vertex array for grid
    GLuint gridVAO, gridVBO;
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);

    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    // Enable vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0); // Unbind VAO after setting up

    // Now bind VAO and draw the grid lines using GL_LINES
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, gridVertices.size() / 3);  // Draw the grid lines
    glBindVertexArray(0);  // Unbind VAO

    // Cleanup
    glDeleteBuffers(1, &gridVBO);
    glDeleteVertexArrays(1, &gridVAO);
};
