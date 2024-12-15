#include "pch.h"
#include "render/ui_context.h"

void render::UIXContext::init(GLFWwindow* window) {

    // ImGUI
    ImGui::CreateContext();

    // Initialize ImGui for GLFW and OpenGL3
    ImGui_ImplGlfw_InitForOpenGL(window, true);  // This should be called only once
    ImGui_ImplOpenGL3_Init("#version 130");     
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable viewports (optional)

    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    // Set up ImGui style
    ImGui::StyleColorsDark();
};


void render::UIXContext::pre_render() {
    // GUI Start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create the docking environment
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    // Set window style variables
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 1.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(0.0f, 0.0f, 0.0f, 1.00f));

    // Create the invisible window with no title bar, no collapse button, and no resize
    ImGui::Begin("InvisibleWindow", nullptr, windowFlags);


    render_toolbar();
  
    // Create dock space for docking windows
    ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");
    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f));

    ImGui::End();

    // Pop style variables and color
    ImGui::PopStyleVar(3);  // Match the three PushStyleVar calls
    ImGui::PopStyleColor(1); // Pop the one PushStyleColor call
};


void render::UIXContext::render() {

    render_inspector();
    render_hierarchy();
    render_assets_hierarchy();
};

void render::UIXContext::post_render() {
  
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Handle viewports (if enabled)
    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();                                // Update platform-specific windows
        ImGui::RenderPlatformWindowsDefault();                         // Render all the windows
        glfwMakeContextCurrent(backup_current_context);                // Restore the current context
    }
};


void render::UIXContext::end()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
void render::UIXContext::render_toolbar()
{
    ImGui::Button("File");
    ImGui::SameLine();
    ImGui::Button("Edit");
    ImGui::SameLine();
    ImGui::Button("Add");
    ImGui::SameLine();
    ImGui::Button("Window");


}
void render::UIXContext::render_inspector()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.5f, 0.5f));          // Override for one window

    // Create main dock space
    ImGui::Begin("Inspector");

    ImGui::DockSpace(ImGui::GetID("Inspector"));

    ImGui::End();
    ImGui::PopStyleVar();
}
void render::UIXContext::render_hierarchy()
{
    ImGui::Begin("Hierarchy");
    // Render hierarchy contents here
    ImGui::End();
};


void render::UIXContext::render_assets_hierarchy()
{
    // Begin the "Assets Hierarchy" window
    ImGui::Begin("Assets Hierarchy");

    // Example structure for the hierarchy:
    // You can expand this to show your game assets (textures, models, etc.)
    ImGui::Text("Assets");

    if (ImGui::CollapsingHeader("Textures")) {
        ImGui::BulletText("Texture1.png");
        ImGui::BulletText("Texture2.png");
        ImGui::BulletText("Texture3.png");
    }

    if (ImGui::CollapsingHeader("Models")) {
        ImGui::BulletText("Model1.obj");
        ImGui::BulletText("Model2.obj");
        ImGui::BulletText("Model3.obj");
    }

    if (ImGui::CollapsingHeader("Sounds")) {
        ImGui::BulletText("Sound1.wav");
        ImGui::BulletText("Sound2.wav");
        ImGui::BulletText("Sound3.wav");
    }

    // End the window
    ImGui::End();
}

