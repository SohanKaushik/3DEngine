#pragma once

#include "pch.h"
#include "ui/viewport.h"
#include "elems/camera.h"
#include "render/ui_context.h"

#include <Engine/inputs/inputhandler.h>


class WindowManager {
private:
    static GLFWwindow* m_window;
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
    void render();

    void Clear();
    void Clean();
    bool isRunning();
    void end();

    void handleInputs();

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    static GLFWwindow* GetWindow();
    std::unique_ptr<ui::Viewport> mViewport = std::make_unique<ui::Viewport>();
    std::unique_ptr<render::UIXContext> mUIx = std::make_unique<render::UIXContext>();


private:
    double lastX, lastY;
    bool firstMouse;

private:
    void set_fullscreen(bool isFullSrn);
};
