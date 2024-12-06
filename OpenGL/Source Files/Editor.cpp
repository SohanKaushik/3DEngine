#include "pch.h"

#include "Editor.h"
#include "window.h"

Editor::Editor(const std::string& app_name)
{
    mWindow = std::make_unique<WindowManager>();
    mWindow->Init(1024, 720, app_name);

}

void Editor::init() {
    std::cout << "Initialized completed." << std::endl;
};

void Editor::loop()
{   
    while (mWindow->isRunning()) {
       
        // Poll for window events
        glfwPollEvents();

        // Clear the screen (set color buffer)
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers (display the rendered content)
        glfwSwapBuffers(mWindow->GetWindow());

        // Debug message to confirm loop is running
        std::cout << "Window is running..." << std::endl;

        // Debug check: If the window is not running, this message will help identify that
        if (glfwWindowShouldClose(mWindow->GetWindow())) {
            std::cout << "Window should close, exiting loop." << std::endl;
        }
    };
};

void Editor::end() {
    std::cout << "End completed." << std::endl;
};