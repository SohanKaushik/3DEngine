#include "Editor.h"

#include "window.h"

Editor::Editor(const std::string& app_name)
{
    mWindow = std::make_unique<WindowManager>();
    mWindow->Init(1024, 720, app_name);

}

void Editor::loop()
{
    while (mWindow->isRunning())
    {
        std::cout << "Enter" << std::endl;
    };
};