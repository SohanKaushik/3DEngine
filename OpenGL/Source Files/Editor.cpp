#include "pch.h"

#include "Editor.h"
#include "window/window.h"
#include "Editor/core/render_image.h"

Editor::Application::Application(const std::string& app_name)
{
    mWindow->Init(1000, 800, app_name);
};


void Editor::Application::loop()
{   
    while (mWindow->isRunning()) {
       
        // Clear the view
        mWindow->pre_render();

        // Render Scene
        mWindow->render();


        // Render end, swap buffers
        mWindow->post_render();
    };
};

void Editor::Application::shutdown() {
    mWindow->end();
};