#include "pch.h"
#include "ui/viewport.h"
#include "Object.h"

using namespace elems;

void ui::Viewport::Init()
{
	std::cout << "Viewport Initialization" << std::endl;
	mShader->load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mCamera = std::make_unique<elems::Camera>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f, 0.1, 2000.0f);

	primitives["cube1"] = new Primitive("cube1");
};

void ui::Viewport::render()
{

	mShader->use();
	//mCamera->UpdateCameraMatrix(*mShader);

	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, -0.5, -2.0f));
	projectionMatrix = glm::perspective(glm::radians(45.0f), 1024.0f / 720.0f, 0.1f, 1000.0f);


	mShader->SetUniformMat4f("view", viewMatrix);
	mShader->SetUniformMat4f("projection", projectionMatrix);


	for (auto& poly : primitives) {
		Primitive* primitive = poly.second;

		glm::mat4 m_model = glm::mat4(1.0f); // Reset to identity
		m_model = glm::rotate(m_model, glm::radians(45.0f), glm::vec3(5.0f, 0.0f, 0.0f));
		mShader->SetUniformMat4f("model", m_model);
		mShader->SetUniform3fv("color", glm::vec3(1.0f, 0.0f, 0.0f));
		primitive->render();
	}

	//mGrid->render();
};




void ui::Viewport::destroy()
{
	mGrid->destroy();
};

