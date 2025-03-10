#include "pch.h"
#include "ui/viewport.h"
#include "Editor/system.h"
#include "Editor/maths/ray_intersection.h"
#include <Editor/maths/intersection_handler.h>
#include "render/ui_context.h"

using namespace elems;
using namespace Editor;

float quadVertices[] = {
	// Positions   // TexCoords
	-1.0f,  1.0f,  0.0f, 1.0f,  // Top-left
	-1.0f, -1.0f,  0.0f, 0.0f,  // Bottom-left
	 1.0f, -1.0f,  1.0f, 0.0f,  // Bottom-right

	-1.0f,  1.0f,  0.0f, 1.0f,  // Top-left
	 1.0f, -1.0f,  1.0f, 0.0f,  // Bottom-right
	 1.0f,  1.0f,  1.0f, 1.0f   // Top-right
};

void ui::Viewport::Init() {
	// Load shaders
	mShader[0].load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mShader[1].load("Resource Files/Shaders/grid.vert", "Resource Files/Shaders/grid.frag");
	mShader[2].load("Resource Files/Shaders/DirectionalShadowMap.vert", "Resource Files/Shaders/DirectionalShadowMap.frag");

	mShader[3].load("Resource Files/Shaders/deferred/deferred.vert", "Resource Files/Shaders/deferred/deferred.frag");
	mShader[4].load("Resource Files/Shaders/deferred/deff_lightpass.vert", "Resource Files/Shaders/deferred/deff_lightpass.frag");
	mShader[5].load("Resource Files/Shaders/plane.vert", "Resource Files/Shaders/plane.frag");

	mFramebuffer->create_buffer(1000, 800);
	mShadowFrameBuffer->create_buffer(2048, 2048);
	gBuffer->create_buffer(2048, 2048);

	// Initialize camera and grid
	mCamera = std::make_unique<Editor::Camera>(
		glm::vec3(0.0f, 0.0f, -10.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 45.0f, 0.1, 1000.0f
	);

	mGrid->Init();
	

	// default entity
	this->def_enit();
};


void ui::Viewport::render() {


	mFramebuffer->bind();
	//// -> rendering mode
	forward();
	/*switch (_rmode) {
		case ui::RenderMode::Forward:  forward();  break;
		case ui::RenderMode::Deferred: deferred(); break;
	}*/

	mGrid->render(mShader[1], mCamera->GetCameraPosition());
	mCamera->UpdateCameraMatrix(mShader[1]);

	

	mFramebuffer->unbind();

	// Display final output in the ImGui window
	this->RenderSceneUI();
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

void ui::Viewport::on_zoom(float offset, float senst) {

	mCamera->UpdateZoom(static_cast<float>(offset) * senst, mShader[0]);
}

void ui::Viewport::RenderSceneUI() {


	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	// Set dark theme
	colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.0f);
	colors[ImGuiCol_Button] = ImVec4(0.25f, 0.25f, 0.25f, 1.0f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.35f, 0.35f, 1.0f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.0f);

	style.FrameRounding = 2.0f;
	style.WindowPadding = ImVec2(8.0f, 8.0f);
	style.ItemSpacing = ImVec2(6.0f, 6.0f);

	// Check if the window is docked
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;

	// If the window is docked, hide the title bar (and its buttons)
	if (ImGui::IsWindowDocked()) {
		windowFlags |= ImGuiWindowFlags_NoTitleBar;
	}


	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.5f, 0.5f));				

	ImGui::Begin("Scene", nullptr, windowFlags);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_size = { viewportPanelSize.x, viewportPanelSize.y };

	// Resize Image Texture too .......(needs to be done)
	mCamera->set_aspect(m_size.x/ m_size.y);
	mCamera->UpdateCameraMatrix(mShader[0]);

	unsigned int _textureID = mFramebuffer->get_texture();
	ImGui::Image(_textureID, ImVec2{ m_size.x, m_size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
}

void ui::Viewport::forward() {

	glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -3.1f, -1.0f));   // Adjust as needed 
	mEntityHandler->update(mShader[0]);

	mShader[0].use();
	mCamera->UpdateCameraMatrix(mShader[0]);

	mShader[0].SetUniform3fv("direction", lightDirection);
};

void ui::Viewport::deferred() {

	// 1. Geometry Pass: Render scene to G-buffer
	gBuffer->bind();
	mShader[3].use();
	//////////////
	mCamera->UpdateCameraMatrix(mShader[3]);
	gBuffer->unbind();

	//// 2. Lighting Pass: Render fullscreen quad with deferred lighting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mShader[4].use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gBuffer->getPositionTexture());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gBuffer->getNormalTexture());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gBuffer->getAlbedoTexture());

	mShader[4].use();
	mShader[4].SetUniform1i("gPosition", 0);
	mShader[4].SetUniform1i("gNormal", 1);
	mShader[4].SetUniform1i("gAlbedo", 2);
	quad(); 

}

Editor::Entity& ui::Viewport::def_enit() {

	auto entity = mEntityHandler->CreateEntity();
	entity->AddComponent<TransformComponent>();
	entity->AddComponent<MeshComponent>().SetMesh(elems::primvtype::cube);
	entity->AddComponent<MaterialComponent>();
	return *entity;
}

void ui::Viewport::quad() {
	static unsigned int quadVAO = 0, quadVBO;

	if (quadVAO == 0) {
		float quadVertices[] = {
			// Positions     // TexCoords
			-1.0f,  1.0f,  0.0f, 1.0f,  // Top-left
			-1.0f, -1.0f,  0.0f, 0.0f,  // Bottom-left
			 1.0f, -1.0f,  1.0f, 0.0f,  // Bottom-right

			-1.0f,  1.0f,  0.0f, 1.0f,  // Top-left
			 1.0f, -1.0f,  1.0f, 0.0f,  // Bottom-right
			 1.0f,  1.0f,  1.0f, 1.0f   // Top-right
		};


		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);

		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

		// Position attribute: 2 floats (x, y)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

		// Texture coordinate attribute: 2 floats (u, v)
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		mShader[4].SetUniformMat4f("model", glm::mat4(1.0f));
		glBindVertexArray(0);
	}

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
