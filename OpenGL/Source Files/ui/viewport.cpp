#include "pch.h"
#include "ui/viewport.h"
#include "Object.h"

using namespace elems;

void ui::Viewport::Init()
{
	std::cout << "Viewport Initialization" << std::endl;
	mShader[0].load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mShader[1].load("Resource Files/Shaders/grid.vert", "Resource Files/Shaders/grid.frag");

	// Camera
	mCamera = std::make_unique<elems::Camera>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f, 0.1, 1000.0f);

	// Grid Axes
	mGrid->Init();


	// Primitvies : { position, rotation, scale }
	mMesh["cube1"] = new Mesh ({ glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(1.0f) });  
	mMesh["cube2"] = new Mesh ({ glm::vec3(3.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(1.0f) });
	
	//Lights
	
};

void ui::Viewport::render() {
  
	mMesh["cube1"]->setColor(glm::vec3(1.0f, 0.0f, 0.0f));

    // Set per-object uniforms and draw
	for (auto& obj : mMesh) {
		glm::mat4 m_model = glm::mat4(1.0f);
		m_model = glm::translate(m_model, obj.second->getPosition());
		m_model = glm::rotate(m_model, glm::radians(0.0f), glm::normalize(obj.second->getRotation()));
		m_model = glm::scale(m_model, obj.second->getScale());

		mShader[0].SetUniformMat4f("model", m_model);
		mShader[0].SetUniform3fv("color", obj.second->getColor());
		obj.second->draw();
	};
	mCamera->UpdateCameraMatrix(mShader[0]);

    // Render Grid
    mGrid->render(mShader[1]);
	mCamera->UpdateCameraMatrix(mShader[1]);


	// Lights 
	//mLight.push_back(std::make_unique<DirectionalLight>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f)));
	mShader[0].use();
	DirectionalLight dirLight(
		glm::vec3(0.2),  // ambient 
		glm::vec3(1.0f),  // diffuse 
		glm::vec3(0),                // specular
		glm::vec3(-1.0, -3.0, 0.0)   // direction
	);

	dirLight.SetLightUniform(mShader[0], "dirLight");
	
}

void ui::Viewport::destroy()
{
	mGrid->destroy();

	for (auto& obj : mMesh) {
		delete obj.second;
	};
	mMesh.clear();
};

void ui::Viewport::on_orbit(float xOffset, float yOffset, float speed, bool constraint) {
	float deltaYaw = xOffset * speed;
	float deltaPitch = yOffset * speed;

	// Update camera orientation based on mouse movement
	mCamera->on_mouse_move(deltaYaw, deltaPitch, constraint);
};

void ui::Viewport::on_zoom(float offset, float senst){

	mCamera->UpdateZoom(static_cast<float>(offset) * senst, mShader[0]);
};


