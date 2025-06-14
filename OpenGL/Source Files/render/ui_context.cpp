#include "pch.h"
#include "render/ui_context.h"
#include <render/framebuffer_handler.h>
#include <thread>

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

    //mViewport = vp;
};


void render::UIXContext::pre_render() {
    // GUI Start
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // Create the docking environment
    ImGuiWindowFlags windowFlags = 
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



    // Create dock space for docking windows
    ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");
    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f));

    ImGui::End();

    // Pop style variables and color
    ImGui::PopStyleVar(3);  // Match the three PushStyleVar calls
    ImGui::PopStyleColor(1); // Pop the one PushStyleColor call
};


void render::UIXContext::render() {

     render_toolbar();
    //ImGui::ShowDemoWindow();
    render_inspector();
    lights();
    materials();
    //render_hierarchy();
    //render_assets_hierarchy();


    ImGui::Begin("Color Buffer");  // Pass pointer to allow closing the window with X button
    ImGui::Text("pointer = %x", render::FrameBufferHandle::RetrieveFrameBuffer("_Picking")->getID());
    //ImGui::Text("size = %d x %d", _selection_texture->getWidth(), _selection_texture->getHeight());
    ImGui::Image((ImTextureID)(intptr_t)render::FrameBufferHandle::RetrieveFrameBuffer("_Picking")->get_texture(), ImVec2(200, 200), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

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
    ImGuiStyle& style = ImGui::GetStyle();

    style.ItemSpacing = ImVec2(15.0f, 5.0f); // Adjust the space between menu items
    style.FramePadding = ImVec2(5.0f, 5.0f); // Adjust the padding inside menu items
    //style.WindowPadding = ImVec2(5.0f, 5.0f); // Adjust the padding inside the menu bar


    if (ImGui::BeginMainMenuBar()) {


        ShowFileMenu();

        // **Edit Menu**
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo")) {
                // Action for Undo
            }
            if (ImGui::MenuItem("Redo")) {
                // Action for Redo
            }
            if (ImGui::MenuItem("Preferences")) {
                // Action for Preferences
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Render")) {
            if (ImGui::MenuItem("Render Image")) {
                /* std::thread renderThread([&]() {
                     rendr_image->create_rendrwin();
                     rendr_image->loop();
                     });
                 renderThread.detach();*/
            }

            if (ImGui::MenuItem("Null")) {
                // Action for About
            }
            ImGui::EndMenu();
        }

        // **View Menu**
        if (ImGui::BeginMenu("View")) {
            if (ImGui::MenuItem("Show Grid")) {
                // Action for Show Grid
            }
            if (ImGui::MenuItem("Hide Grid")) {
                // Action for Hide Grid
            }
            ImGui::EndMenu();
        }

        // **Window Menu**
        if (ImGui::BeginMenu("Add")) {

            if (ImGui::BeginMenu("Mesh")) {
                ImGui::PushID("Plane");
                if (ImGui::MenuItem("Plane")) {
                    auto plane = Editor::EntityHandler::CreateEntity();
                    plane->AddComponent<Editor::TransformComponent>();
                    plane->AddComponent<Editor::MeshComponent>().SetMesh(elems::PrimitiveType::plane);
                }
                ImGui::PopID();  // Pop the ID after rendering

                ImGui::PushID("Sphere");
                if (ImGui::MenuItem("Sphere")) {
                    auto sphere = Editor::EntityHandler::CreateEntity();
                    sphere->AddComponent<Editor::TransformComponent>();
                    sphere->AddComponent<Editor::MeshComponent>().load("Resource Files/models/sphere.obj");
                }
                ImGui::PopID();

                ImGui::PushID("Cube");
                if (ImGui::MenuItem("Cube")) {
                    auto cube = Editor::EntityHandler::CreateEntity();
                    cube->AddComponent<Editor::TransformComponent>();
                    cube->AddComponent<Editor::MaterialComponent>();
                    cube->AddComponent<Editor::MeshComponent>().SetMesh(elems::PrimitiveType::cube);
                }
                ImGui::PopID();

                ImGui::PushID("Monkey");
                if (ImGui::MenuItem("Monkey")) {
                    auto monkey = Editor::EntityHandler::CreateEntity();
                    monkey->AddComponent<Editor::TransformComponent>();
                    monkey->AddComponent<Editor::MaterialComponent>();
                    monkey->AddComponent<Editor::MeshComponent>().load("Resource Files/models/monkey.obj");
                }
                ImGui::PopID();

                ImGui::PushID("Porsche");
                if (ImGui::MenuItem("Porsche")) {
                    auto porsche = Editor::EntityHandler::CreateEntity();
                    porsche->AddComponent<Editor::TransformComponent>();
                    porsche->AddComponent<Editor::MeshComponent>().load("Resource Files/models/porsche.obj");
                }
                ImGui::PopID();

                ImGui::PushID("Light");
                if (ImGui::MenuItem("Directional")) {
                    auto dirLight = Editor::EntityHandler::CreateEntity();
                    //dirLight->AddComponent<Editor::TransformComponent>();

                    //// would add gizmo later
                    //dirLight->GetComponent<Editor::TransformComponent>()->SetScale(glm::vec3(0.15, 0.15, 0.15));
                    //dirLight->AddComponent<Editor::MeshComponent>().load("Resource Files/models/sphere.obj");
                    //dirLight->AddComponent<Editor::LightComponent>().SetDirectionalLight();
                }
                ImGui::PopID();

                ImGui::EndMenu();
            }

            // Now the mesh subsets should appear in the correct order above


            if (ImGui::MenuItem("Camera")) {
                //...
                auto entity = Editor::EntityHandler::GetSelectedEntity();

                // std::cout << glm::to_string(entity->GetPosition()) << std::endl;
            };

            ImGui::EndMenu();
        }

        // **Help Menu**
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("Documentation")) {
                // Action for Documentation
            }
            if (ImGui::MenuItem("About")) {
                // Action for About
            }
            ImGui::EndMenu();
        }

        // Somewhere globally or static
        static bool showPickingDebug = false;

        // In your Debug menu code:
        if (ImGui::BeginMenu("Debug")) {
            if (ImGui::MenuItem("Picking Buffer", NULL, &showPickingDebug)) {
                // toggles showPickingDebug automatically
            }
            ImGui::EndMenu();
        }



        ImGui::EndMainMenuBar();
    }
}



void render::UIXContext::ShowFileMenu()
{
    // Set the size and constraints for the popup window
    //ImGui::SetNextWindowSize(ImVec2(300.0f, 200.0f));  // Increase size of the popup
    ImGui::SetNextWindowSizeConstraints(ImVec2(200.0f, 250.0f), ImVec2(200, 200.0f)); // Constraints for resizing

    // Apply padding and rounding to the popup window
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20.0f, 20.0f));  // Set padding inside the window
    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 5.0f);  // Apply rounding to the window corners

    // **File Menu**
    if (ImGui::BeginMenu("File")) {
        // Menu items
        if (ImGui::MenuItem("New File")) {
            // Action for New File
        }
        if (ImGui::MenuItem("Open File")) {
            // Action for Open File
        }
        if (ImGui::MenuItem("Save File")) {
            // Action for Save File
        }

        ImGui::Separator();
        if (ImGui::MenuItem("Quit")) {
            std::cout << "...shutdown..." << std::endl;
            exit(0);
        }

        ImGui::EndMenu();
    }

    // Pop the style variables
    ImGui::PopStyleVar(2);
}


void render::UIXContext::render_inspector()
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.08f, 0.08f, 0.08f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.16f, 0.16f, 0.16f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.16f, 0.16f, 0.16f, 1.0f));


    if (ImGui::Begin("Inspector", nullptr))
    {
        auto entity = Editor::EntityHandler::GetSelectedEntity();
        if (!entity) {
            ImGui::End();
            ImGui::PopStyleColor(3);
            return;
        }
        auto transform = entity->GetComponent<Editor::TransformComponent>();
        auto mesh = entity->GetComponent<Editor::MeshComponent>();
        glm::vec3& position = transform->GetPosition();
        glm::vec3& scale = transform->GetScale();
        glm::vec3& rotation = transform->GetRotation();
        glm::vec3 color = glm::vec3(1.0f);

        float drag_senstivity = 0.5f;

        ImGui::Text("Transform");
        ImGui::Separator();
        // Position Controls (X, Y, Z)
        ImGui::Text("Position");
        ImGui::DragFloat("x###position_x", &position.x, drag_senstivity, -1000.0f, 1000.0f);
        ImGui::DragFloat("y###position_y", &position.y, drag_senstivity, -1000.0f, 1000.0f);
        ImGui::DragFloat("z###position_z", &position.z, drag_senstivity, -1000.0f, 1000.0f);

        // Rotation Controls (X, Y, Z)
        ImGui::Text("Rotation");
        ImGui::DragFloat("x###rotation_x", &rotation.x, drag_senstivity, -360.0f, 360.0f);
        ImGui::DragFloat("y###rotation_y", &rotation.y, drag_senstivity, -360.0f, 360.0f);
        ImGui::DragFloat("z###rotation_z", &rotation.z, drag_senstivity, -360.0f, 360.0f);

        // Scale Controls (X, Y, Z)
        ImGui::Text("Scale");
        ImGui::DragFloat("x###scale_x", &scale.x, drag_senstivity * 0.2f, 0.0f, 100.0f);
        ImGui::DragFloat("y###scale_y", &scale.y, drag_senstivity * 0.2f, 0.0f, 100.0f);
        ImGui::DragFloat("z###scale_z", &scale.z, drag_senstivity * 0.2f, 0.0f, 100.0f);

       

      ImGui::End();

    }

    ImGui::PopStyleColor(3);
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
void render::UIXContext::lights()
{
    auto entity = Editor::EntityHandler::GetSelectedEntity();
    if (!entity || !entity->HasComponent<Editor::LightComponent>()) {
        return;
    }

    ImGui::Begin("Lights");

    auto lightcom = Editor::EntityHandler::GetSelectedEntity()->GetComponent<Editor::LightComponent>();
    auto* light = lightcom->GetLight();

    if (ImGui::BeginTabBar("LightTabs"))
    {
        if (ImGui::BeginTabItem("Sun"))
        {
            glm::vec3& color = lightcom->GetLightData().albedo;
            float& strength = lightcom->GetLightData().strength;
            //float& angle = lightcom->GetLight().

            ImGui::ColorEdit3("Color", glm::value_ptr(color));
            ImGui::DragFloat("Strength", &strength, 0.1f, 0.0f, 10.0f);
            //ImGui::DragFloat("Angle", &angle, 0.1f, 0.0f, 90.0f);

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Point"))
        {
            // Point light controls here
            ImGui::Text("Point Light Settings");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Spot"))
        {
            // Spot light controls here
            ImGui::Text("Spot Light Settings");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void render::UIXContext::materials()
{
    ImGui::Begin("Materials");
    auto entity = Editor::EntityHandler::GetSelectedEntity();
    if (!entity) {
        ImGui::End();
        return;
    }
    auto component = entity->GetComponent<Editor::MaterialComponent>();
    auto* material = component->GetMaterial();

    // downcasting from IMaterial to Material<Shader>
    auto* shader = dynamic_cast<elems::Material<elems::Lambert>*>(material);

    // accessing color 
    glm::vec3& color = shader->GetModel()._lambert.albedo;


    static int selectedOption = 0;
    const char* options[] = { "Lambert", "Phong", "Blinn Phong" };

    if (ImGui::BeginCombo("Type", options[selectedOption]))
    {
        for (int i = 0; i < IM_ARRAYSIZE(options); i++)
        {
            bool isSelected = (selectedOption == i);
            if (ImGui::Selectable(options[i], isSelected))
            {
                selectedOption = i;
            }
            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    // Display a small color box
    ImGui::Text("Color");
    if (ImGui::ColorButton("##color_button", ImVec4(color.r, color.g, color.b, 1.0f), ImGuiColorEditFlags_NoTooltip, ImVec2(150, 15))) {
        // When clicked, show the color picker
        ImGui::OpenPopup("Color Picker");
    }

    // Display the color picker if the box was clicked
    if (ImGui::BeginPopup("Color Picker")) {
        ImGui::ColorPicker3("##picker", glm::value_ptr(color));
        ImGui::EndPopup();
    }
    ImGui::End();
}
