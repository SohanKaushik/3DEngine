#pragma once

#include <GLFW/glfw3.h>
#include <string>

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
};
