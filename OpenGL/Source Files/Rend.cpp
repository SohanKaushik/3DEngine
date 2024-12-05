
#include <glm/glm.hpp>
#include "Rend.h"
#include "Camera.h"
#include "window.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>



Rend::Rend(Camera& cam) : m_camera(cam)
{};


void Rend::Clear() const {
	
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
void Rend::SetModelPosition(glm::vec3 translation = glm::vec3(0,0,0)) {
    m_modelPosition = translation;
    model = glm::translate(glm::mat4(1.0), m_modelPosition);
};

void Rend::SetModelScale() {
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
};

void Rend::SetModelRotate(glm::vec3 axis, float radian) {
    model = m_modelRotate;
    model = glm::rotate(m_modelRotate, glm::radians(radian), axis);
};

void Rend::SetModelColor(glm::vec3 color, const std::string& uniformName, Shader& shader )
{
    shader.SetUniform3fv(uniformName, color);
};


// All Matrix Transform
void Rend::UpdateMatrix(Shader& shader, const std::vector <std::string>& uniformNames, Camera& camera) {
	//glm::mat4 mvp = camera.GetProjectionMatrix() * camera.GetViewMatrix() * model;
    // No error checking of indexing

    
    shader.SetUniformMat4f(uniformNames[0], model);
    shader.SetUniformMat4f(uniformNames[1], camera.GetProjectionMatrix());
    shader.SetUniformMat4f(uniformNames[2], camera.GetViewMatrix());
    shader.SetUniform3fv(uniformNames[3], camera.GetCameraPosition());
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
    

    // Create grid lines data (position + color)
    std::vector<float> gridVertices;
    int gridSize = 1000;

 

    glm::vec3 xColor = glm::vec3(0.886, 0.376, 0.357); //red
    glm::vec3 yColor = glm::vec3(0.482, 0.8, 0.482);

    glm::vec3 lineColor = gridColor;                    // Default grid color

    // Draw vertical lines (XZ plane)
    for (float x = -gridSize; x <= gridSize; x += spacing) {
        glm::vec3 color = (fabs(x) == 0) ? xColor : lineColor; // Red if x is near origin
        gridVertices.push_back(x); gridVertices.push_back(0.0f); gridVertices.push_back(-gridSize); // Start
        gridVertices.push_back(color.r); gridVertices.push_back(color.g); gridVertices.push_back(color.b);

        gridVertices.push_back(x); gridVertices.push_back(0.0f); gridVertices.push_back(gridSize); // End
        gridVertices.push_back(color.r); gridVertices.push_back(color.g); gridVertices.push_back(color.b);
    }

    // Draw horizontal lines (XZ plane)
    for (float z = -gridSize; z <= gridSize; z += spacing) {
        glm::vec3 color = (fabs(z) == 0) ? yColor : lineColor; // Red if z is near origin
        gridVertices.push_back(-gridSize); gridVertices.push_back(0.0f); gridVertices.push_back(z); // Start
        gridVertices.push_back(color.r); gridVertices.push_back(color.g); gridVertices.push_back(color.b);

        gridVertices.push_back(gridSize); gridVertices.push_back(0.0f); gridVertices.push_back(z); // End
        gridVertices.push_back(color.r); gridVertices.push_back(color.g); gridVertices.push_back(color.b);
    }

    // Bind vertex array for grid
    GLuint gridVAO, gridVBO;
    glGenVertexArrays(1, &gridVAO);
    glGenBuffers(1, &gridVBO);

    glBindVertexArray(gridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    // Enable vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);       // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color attribute
    glEnableVertexAttribArray(1);
    glBindVertexArray(0); // Unbind VAO after setting up

    // Now bind VAO and draw the grid lines using GL_LINES
    glBindVertexArray(gridVAO);
    glDrawArrays(GL_LINES, 0, gridVertices.size() / 6);  // Each vertex has 6 floats (3 for position, 3 for color)
    glBindVertexArray(0);  // Unbind VAO

    // Cleanup
    glDeleteBuffers(1, &gridVBO);
    glDeleteVertexArrays(1, &gridVAO);
};
