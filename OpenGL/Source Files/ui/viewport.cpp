#include "pch.h"
#include "ui/viewport.h"
#include "Object.h"

using namespace elems;

void ui::Viewport::Init()
{
	std::cout << "Viewport Initialization" << std::endl;
	mShader->load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mCamera = std::make_unique<elems::Camera>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f, 0.1, 1000.0f);

	mMesh["cube1"] = new Mesh ({ glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f) });
};

void ui::Viewport::render()
{

	mShader->use();

	mCamera->UpdateCameraMatrix(*mShader);
	
	mMesh["cube1"]->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 m_model = glm::mat4(1.0f);
	for (auto& pair : mMesh) {
		pair.second->draw();
	}

	float rotationSpeed = 45.0f;  // Degrees per second
	float angle = glfwGetTime() * rotationSpeed;  

	m_model = glm::rotate(m_model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f));  

	mShader->SetUniformMat4f("model", m_model);
	mShader->SetUniform3fv("color", glm::vec3(1.0f, 0.0f, 0.0f));
	
	mGrid->render();
};




void ui::Viewport::destroy()
{
	mGrid->destroy();
	
}

void ui::Viewport::on_orbit(double mouseX, double mouseY, float speed, bool constraint)
{
	if (firstMouse) {
		lastX = mouseX;
		lastY = mouseY;
		firstMouse = false;
	}

	// Incrementally apply changes (don't reset)
	float xOffset = (mouseX - lastX) * speed;
	float yOffset = (lastY - mouseY) * speed;

	// Update camera position or orientation based on these deltas
	mCamera->on_mouse_move(xOffset, yOffset, true);  // Orbit based on mouse movement

	lastX = mouseX;
	lastY = mouseY;
};

