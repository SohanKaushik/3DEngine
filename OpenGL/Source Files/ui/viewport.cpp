#include "pch.h"
#include "ui/viewport.h"
#include "Object.h"

using namespace elems;


void ui::Viewport::Init()
{
	//Frame Buffer
	mFramebuffer->create_buffer(1000, 800);

	mShader[0].load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mShader[1].load("Resource Files/Shaders/grid.vert", "Resource Files/Shaders/grid.frag");

	// Camera
	mCamera = std::make_unique<elems::Camera>(
		glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f, 0.1, 1000.0f);

	// Grid Axes
	mGrid->Init();

	// Primitvies : { position, rotation, scale }
	mMesh["cube1"] = std::make_unique<elems::Mesh>(
		Transform{ glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(0.0f, 0.0f, 0.0f),  glm::vec3(1.0f) });  

	mMesh["cube2"] = std::make_unique<elems::Mesh>(
		Transform{ glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f) });
	
	//Lights
};

void ui::Viewport::render() {

	//Frame Buffer
	mFramebuffer->bind();

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
	mGrid->render(mShader[1], mCamera->GetCameraPosition());
	//mGrid->render(mShader[1]);
	mCamera->UpdateCameraMatrix(mShader[1]);

	// Frame Buffer End
	mFramebuffer->unbind();

	// Lights 
	//mLight.push_back(std::make_unique<DirectionalLight>(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f), glm::vec3(1.0f)));
	mShader[0].use();
	DirectionalLight dirLight(
		glm::vec3(0.2),              // ambient 
		glm::vec3(1.0f),             // diffuse 
		glm::vec3(0),                // specular
		glm::vec3(-1.0, -3.0, 0.0)   // direction
	);

	dirLight.SetLightUniform(mShader[0], "dirLight");

	this->RenderSceneUI();
};

void ui::Viewport::destroy()
{
	mGrid->destroy();
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
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.5f, 0.5f)); // Override for one window

	ImGui::Begin("Scene", nullptr, windowFlags);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_size = { viewportPanelSize.x, viewportPanelSize.y };

	// Resize Image Texture too .......(needs to be done)

	mCamera->set_aspect(m_size.x / m_size.y);
	mCamera->UpdateCameraMatrix(mShader[0]);

	// add rendered texture to ImGUI scene window
	unsigned int textureID = mFramebuffer->get_texture();
	ImGui::Image(textureID, ImVec2{ m_size.x, m_size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
};


