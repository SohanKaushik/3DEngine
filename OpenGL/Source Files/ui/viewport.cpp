#include "pch.h"
#include "ui/viewport.h"
#include "Object.h"

using namespace elems;
GLuint quadVAO, quadVBO, quadEBO;

std::vector<float> quadVertices = {
	// Positions        // Texture coordinates
	-1.0f, -1.0f, 0.0f, 0.0f, 1.0f,  // Bottom-left
	 1.0f, -1.0f, 0.0f, 1.0f, 1.0f,  // Bottom-right
	 1.0f,  1.0f, 0.0f, 1.0f, 0.0f,  // Top-right
	-1.0f,  1.0f, 0.0f, 0.0f, 0.0f   // Top-left
};



// Indices for the quad (2 triangles)
std::vector<unsigned int> quadIndices = { 0, 2, 1, 2, 0, 3 };



void ui::Viewport::Init()
{

	mShader[0].load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
	mShader[1].load("Resource Files/Shaders/grid.vert", "Resource Files/Shaders/grid.frag");
	mShader[2].load("Resource Files/Shaders/DirectionalShadowMap.vert", "Resource Files/Shaders/DirectionalShadowMap.frag");
	mShader[3].load("Resource Files/Shaders/plane.vert", "Resource Files/Shaders/plane.frag");


	//Shadow Frame Buffer
	mShadowFrameBuffer->create_buffer(2048, 2048);

	// Frame Buffer
	mFramebuffer->create_buffer(1000, 800);


	// Camera
	mCamera = std::make_unique<elems::Camera>(
		glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 45.0f, 0.1, 1000.0f);

	// Grid Axes
	mGrid->Init();

	// Entities
	this->AddEntity(mesh, PrimitiveType::Cube);
	this->AddEntity(mesh, PrimitiveType::Cube);
	this->AddEntity(mesh, PrimitiveType::Cube);
	this->AddEntity(mesh, PrimitiveType::Cube);
	this->AddEntity(mesh, PrimitiveType::Cube);
	//this->AddEntity(mesh, PrimitiveType::Plane);
	//this->AddEntity(light);


	//dump
	//renderQuad();
};

void ui::Viewport::render() {

	glEnable(GL_DEPTH_TEST);
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);  // Near and far planes adjusted
	glm::vec3 lightPos = glm::vec3(10.0f, 10.0f, 10.0f); // Light position
	glm::vec3 lightTarget = glm::vec3(0.0f);            // Target of the light
	glm::vec3 lightUp = glm::vec3(0.0f, 1.0f, 0.0f);    // Up direction
	glm::mat4 lightView = glm::lookAt(lightPos, lightTarget, lightUp);
	glm::mat4 lightSpaceMatrix = lightProjection * lightView;

	////std::cout << glm::to_string(lightSpaceMatrix) << std::endl;

	mShader[2].use();
	mShader[2].SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);

	// Pre-Shadow pass
	glDepthFunc(GL_LESS);
	mShadowFrameBuffer->bind();   
	glClear(GL_DEPTH_BUFFER_BIT);  
	RenderEntities();   
	mShadowFrameBuffer->unbind();    


	// Main rendering
	mFramebuffer->bind();


	mShader[3].use();
	mCamera->UpdateCameraMatrix(mShader[3]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mShadowFrameBuffer->get_dtexture());  
	


	mShader[3].SetUniform1f("shadowMap", 0);
	renderQuad();
	


	// Render Grid
	mGrid->render(mShader[1], mCamera->GetCameraPosition());
	mCamera->UpdateCameraMatrix(mShader[1]);

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
	
	// Frame Buffer End
	mFramebuffer->unbind();
	this->RenderSceneUI();
};

void ui::Viewport::destroy()
{
	mGrid->destroy();
	//mMesh.clear();
	mEntity.clear();
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
	//mCamera->UpdateCameraMatrix(mShader[0]);

	// add rendered texture to ImGUI scene window
	unsigned int textureID = mFramebuffer->get_texture();
	ImGui::Image(textureID, ImVec2{ m_size.x, m_size.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor(3);
}

static float xOffset = 0.0f;
void ui::Viewport::AddEntity(elems::EntityType type, PrimitiveType meshtype) {

	switch (type) {
		case elems::mesh: {
			auto cube = std::make_shared<MeshEntity>(
				meshtype,
				Transform{ glm::vec3(xOffset, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)},
				glm::vec3(1.0f, 0.0f, 0.0f)
			);
			xOffset += 3.0f;
			mEntity.push_back(cube);
			std::cout << "Added entity to mEntity. Size: " << mEntity.size() << std::endl;
			break;
		}
		case elems::light:
			std::cerr << "Light is not yet available" << std::endl;
			break;
		default:
			break;
	}
}

void ui::Viewport::renderQuad() {

	//mShader[3].use();
	mShader[3].SetUniformMat4f("model", glm::mat4(1.0f));

	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	glGenBuffers(1, &quadEBO);

	// Bind VAO
	glBindVertexArray(quadVAO);
	// Bind VBO and upload data
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, quadVertices.size() * sizeof(float), quadVertices.data(), GL_STATIC_DRAW);

	// Bind EBO and upload data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, quadIndices.size() * sizeof(unsigned int), quadIndices.data(), GL_STATIC_DRAW);

	// Set position attribute (location 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Set texture coordinate attribute (location 2)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(quadVAO);  // Bind the quad VAO
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // Draw the full-screen quad
	glBindVertexArray(0);   // Unbind the VAO
};

void ui::Viewport::RenderEntities() {

	for (const auto& entity : mEntity) {
		if (entity) {
			entity->render(mShader[2]);
			mEntity[1]->setPosition(glm::vec3(0.0, 2.0f, 0.0f));
			mEntity[1]->setRotation(glm::vec3(0.0f, -90.0f, 0.0f));
			mEntity[1]->setScale(glm::vec3(2.0f));
			mEntity[0]->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
			mEntity[0]->setPosition(glm::vec3(0.0, 3.0f, 0.1f));

			//mEntity[1]->setScale(glm::vec3(8.0f, 0.001, 8.0f));
		}
		else std::cerr << "Null entity encountered in mEntity!" << std::endl;
	}

};



