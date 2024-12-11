#include "pch.h"
#include "ui/viewport.h"
#include "Object.h"

using namespace elems;

void ui::Viewport::Init()
{
	std::cout << "Viewport Initialization" << std::endl;
	mShader[0].load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mShader[1].load("Resource Files/Shaders/grid.vert", "Resource Files/Shaders/grid.frag");

	mCamera = std::make_unique<elems::Camera>(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f, 0.1, 1000.0f);

	mGrid->Init();

	mMesh["cube1"] = new Mesh ({ glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f) });
};

void ui::Viewport::render() {
  
    mCamera->UpdateCameraMatrix(mShader[0]);
    glm::mat4 m_model = glm::mat4(1.0f);

    // Set per-object uniforms and draw
    for (auto& pair : mMesh) {
        // Set position and model matrix
        m_model = glm::translate(m_model, pair.second->getPosition());

        // Send model matrix and object color to the shader
        mShader[0].SetUniformMat4f("model", m_model);
        mShader[0].SetUniform3fv("color", glm::vec3(1.0f, 0.0f, 0.0f));

        // Draw the mesh
        pair.second->draw();
    }

    // Render Grid
    mGrid->render(mShader[1]);
	mCamera->UpdateCameraMatrix(mShader[1]);
}





void ui::Viewport::destroy()
{
	mGrid->destroy();

};

void ui::Viewport::on_orbit(float xOffset, float yOffset, float speed, bool constraint) {
	float deltaYaw = xOffset * speed;
	float deltaPitch = yOffset * speed;

	// Update camera orientation based on mouse movement
	mCamera->on_mouse_move(deltaYaw, deltaPitch, constraint);
};

void ui::Viewport::on_zoom(float offset, float senst){

	//Distance based senstivity
	float distance = mCamera->GetDistance();
	float dMIn = 0.0f;
	float dMax = 10.0f;

	float distanceFac = glm::smoothstep(dMIn, dMax, distance);
	//float zoomFac = glm::lerp(1.0f, 0.2f, distanceFac);

	mCamera->UpdateZoom(static_cast<float>(-offset) * senst);
};


