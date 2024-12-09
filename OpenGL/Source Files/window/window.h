#pragma once

#include "pch.h"
#include "ui/viewport.h"

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

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    GLFWwindow* GetWindow();
    std::unique_ptr<ui::Viewport> mViewport = std::make_unique<ui::Viewport>();
};
