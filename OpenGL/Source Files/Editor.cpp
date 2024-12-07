#include "pch.h"

#include "Editor.h"
#include "window/window.h"
#include "ui/viewport.h"

Editor::Editor(const std::string& app_name)
{
    mWindow = std::make_unique<WindowManager>();
    mViewport = std::make_unique<ui::Viewport>();

    mWindow->Init(1024, 720, app_name);

}


void Editor::loop()
{   
    while (mWindow->isRunning()) {
       
        // Clear the view
        mWindow->pre_render();
        mViewport->render();
       
        // Render end, swap buffers
        mWindow->post_render();
    };
};

void Editor::shutdown() {
    mWindow->end();
    mViewport->destroy();
};