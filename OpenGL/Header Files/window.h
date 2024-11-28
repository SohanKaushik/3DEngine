#pragma once
#include <GLFW/glfw3.h>



class WindowManager {
private:
    static GLFWwindow* m_window;
    static int m_windowWidth;
    static int m_windowHeight;

public:
    static void WindowInit(int width, int height);
    static GLFWwindow* GetWindow();
    static int GetWindowWidth();
    static int GetWindowHeight();
    static void UpdateWindowSize();  // Function to update window size after creation or resizing
};