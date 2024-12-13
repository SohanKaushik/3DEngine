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


    // Set up ImGui style
    ImGui::StyleColorsDark();
};

void render::UIXContext::pre_render(){

    //GUI Start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
};

void render::UIXContext::render() {
    // Create main dock space
    ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoDocking);
    ImGui::DockSpace(ImGui::GetID("Editor"));
    ImGui::End();
    // Create UI window

    ImGui::Begin("UI Window");
    ImGui::DockSpace(ImGui::GetID("Viewport"));
   
    ImGui::End();

    //// Add your ImGui UI elements here
    //ImGui::Begin("Example Window");

    //ImGui::ShowDemoWindow();
    //ImGui::End();
};

void render::UIXContext::post_render() {
  
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Handle viewports (if enabled)
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();  // Update platform-specific windows
        ImGui::RenderPlatformWindowsDefault();  // Render all the windows
        glfwMakeContextCurrent(backup_current_context);  // Restore the current context
    }
};


void render::UIXContext::end()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
};