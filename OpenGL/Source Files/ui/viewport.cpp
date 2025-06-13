#include "pch.h"
#include "ui/viewport.h"

#include <Engine/inputs/inputhandler.h>
#include <elems/light/light.h>

using namespace elems;
using namespace Editor;
using namespace Engine::Inputs;



void ui::Viewport::Init() {

	// Load shaders
	mShader[0].load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mShader[1].load("Resource Files/Shaders/grid.vert", "Resource Files/Shaders/grid.frag");
	mShader[2].load("Resource Files/Shaders/DirectionalShadowMap.vert", "Resource Files/Shaders/DirectionalShadowMap.frag");
	mShader[3].load("Resource Files/Shaders/plane.vert", "Resource Files/Shaders/plane.frag");
	mShader[4].load("Resource Files/Shaders/depth_test.vert", "Resource Files/Shaders/depth_test.frag");


	render::FrameBufferHandle::AddFrameBuffer(
		std::move(mFramebuffer),
		render::FrameBufferHandle::FrameBufferType::Default, "_default", 1000, 800);


	mCamera = std::make_unique<Editor::Camera>(
		glm::vec3(0.0f, 0.0f, -10.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		-90.0f, 0.0f, 45.0f, 0.1f, 1000.0f
	);
	_selection = std::make_unique<Editor::Selection>();

	mGrid->Init();


	// default entity
	this->def_enit();
};


void ui::Viewport::render() {


	// ------------------------------------------
	// | SELECTION PASS |
	// ------------------------------------------
	_selection->render(mCamera.get());
	// # Render entities into an offscreen framebuffer with unique colors assigned to each entity.
	// # These unique colors act as IDs that can be read back using glReadPixels.
	// # Later, the mouse position is used to read the color under the cursor,
	//   allowing identification of the selected entity.


	// ------------------------------------------
	// | MAIN PASS |			
	// ------------------------------------------
	mShader[0].use();
	render::FrameBufferHandle::RetrieveFrameBuffer("_default")->bind();


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);         
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);  // Write 1 where object drawn
	glStencilMask(0xFF);                        // Enable writing to stencil

	//mCamera->UpdateCameraMatrix(mShader[0]);
	Editor::EntityHandler::render(mShader[0], *mCamera);  // normal draw




	// ------------------------------------------
	// | LIGhTING PASS |
	// ------------------------------------------
	EntityHandler::rlight(mShader[0]);
	//glm::vec3 lightDirection = glm::normalize(glm::vec3(-1.0f, -3.0f, -1.0f)); // Adjust as needed 
	//DirectionalLight dirLight(
	//	glm::vec3(0.2f),              // Ambient
	//	glm::vec3(1.0f),              // Diffuse
	//	glm::vec3(0.0f),              // Specular
	//	lightDirection                // Direction
	//);
	//dirLight.SetLightUniform(mShader[0], "dirLight");

	// ------------------------------------------
	// | OUTLINE STENCIL PASS |
	// ------------------------------------------
	_selection->highlight(mCamera.get()); 


	// ------------------------------------------
	// | GRID PASS |
	// ------------------------------------------
	mGrid->render(mShader[1], mCamera->GetCameraPosition());
	mCamera->UpdateCameraMatrix(mShader[1]);


	// -> END OF FRAMEBUFFEER
	render::FrameBufferHandle::RetrieveFrameBuffer("_default")->unbind();

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

	//// If the window is docked, hide the title bar (and its buttons)
	if (ImGui::IsWindowDocked()) {
		windowFlags |= ImGuiWindowFlags_NoTitleBar;
	}


	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.5f, 0.5f));

	ImGui::Begin("Scene", nullptr);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	m_size = { viewportPanelSize.x, viewportPanelSize.y };

	// Resize Image Texture too .......(needs to be done)
	mCamera->set_aspect(m_size.x / m_size.y);
	//std::cout<< glm::to_string(m_size) << std::endl;
	mCamera->UpdateCameraMatrix(mShader[0]);

	// add rendered texture to ImGUI scene window
	unsigned int textureID = render::FrameBufferHandle::RetrieveFrameBuffer("_default")->get_texture();

	ImGui::Image(textureID, ImVec2{ m_size.x, m_size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
}

Entity& ui::Viewport::def_enit() {

	auto entity = Editor::EntityHandler::CreateEntity();
	entity->AddComponent<TransformComponent>();
	entity->AddComponent<MeshComponent>().GetMesh()->load("Resource Files/models/monkey.obj");
	entity->AddComponent<MaterialComponent>();
	return *entity;
}  