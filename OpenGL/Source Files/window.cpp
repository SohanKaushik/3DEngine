#include <glad/glad.h>
#include "window.h"
#include <iostream>

// Initialize static members
GLFWwindow* WindowManager::m_window = nullptr;
int WindowManager::m_windowWidth = 800;
int WindowManager::m_windowHeight = 600;


void WindowManager::WindowInit(int width, int height)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);

    m_window = glfwCreateWindow(width, height, "Window", NULL, NULL);
    if (m_window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return; // Exit early if window creation fails
    }

    glfwMakeContextCurrent(m_window);

    // Load OpenGL functions using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return; // Exit early if GLAD fails
    }

    // Initialize window size
    m_windowWidth = width;
    m_windowHeight = height;
}

GLFWwindow* WindowManager::GetWindow()
{
    return m_window;
}

int WindowManager::GetWindowWidth()
{
    return m_windowWidth;
}

int WindowManager::GetWindowHeight()
{
    return m_windowHeight;
}

// Function to update window size if it has changed (called every frame or when resizing)
void WindowManager::UpdateWindowSize()
{
    if (m_window != nullptr) {
        glfwGetFramebufferSize(m_window, &m_windowWidth, &m_windowHeight);
    }
}
