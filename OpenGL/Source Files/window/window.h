#pragma once

#include "pch.h"
#include "ui/viewport.h"
#include "elems/camera.h"
#include "render/ui_context.h"

class WindowManager {
private:
    GLFWwindow* m_window;
    int m_windowWidth;
    int m_windowHeight;

public:
    WindowManager();
    ~WindowManager();

    bool Init(int width, int height, const std::string& appName);
    int GetWindowWidth();
    int GetWindowHeight();
    void UpdateWindowSize();

    void pre_render();
    void post_render();
    void end();
    void render();

    void Clear();
    void Clean();
    bool isRunning();

    void handleInputs();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    GLFWwindow* GetWindow();
    std::unique_ptr<ui::Viewport> mViewport = std::make_unique<ui::Viewport>();
    std::unique_ptr<elems::Camera> mCamera = std::make_unique<elems::Camera>();
    std::unique_ptr<render::UIXContext> mUIx = std::make_unique<render::UIXContext>();

    InputManager& input = InputManager::getInstance();

private:
    double lastX, lastY;
    bool firstMouse;

private:
    std::shared_ptr<Editor::EntityHandler> mEntityHandler = Editor::EntityHandler::GetInstance();;
    void set_fullscreen(bool isFullSrn);
};
