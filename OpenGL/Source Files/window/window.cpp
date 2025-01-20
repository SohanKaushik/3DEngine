#include "pch.h"

#include "window.h"


WindowManager::WindowManager()
    : m_windowWidth(800), m_windowHeight(600), m_window(nullptr) 
{};

WindowManager::~WindowManager() {
 
    mUIx->end();
    mViewport->destroy();
    glfwDestroyWindow(m_window);
    glfwTerminate();
};

bool WindowManager::Init(int width, int height , const std::string& appName)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DEPTH_BITS, 24);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(width, height, appName.c_str(), NULL, NULL);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1; // Exit early if window creation fails
    }

    // window context
    glfwMakeContextCurrent(m_window);

    // Load OpenGL functions using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1; // Exit early if GLAD fails
    }
    
    glEnable(GL_DEPTH_TEST);

    //glfwSwapInterval(0);
    glDepthFunc(GL_LESS);         // Depth test function (default is GL_LESS)
    glEnable(GL_CULL_FACE);       // Optional: Enable backface culling

    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // Multi-Sampling 
    glEnable(GL_MULTISAMPLE);

    // Full Screen
    set_fullscreen(false);

    // Initialize window size
    m_windowWidth = width;
    m_windowHeight = height;

    // Set the resize callback
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

   
    // Viewport Init
    mViewport->Init();

    // Inputs Init
    input.Initialize(this->m_window);

    // UI context
    mUIx->init(this->m_window, mViewport.get());

    return true;
}

void WindowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); // Update the OpenGL viewport
    std::cout << "Viewport updated to: " << width << "x" << height << std::endl;
};

GLFWwindow* WindowManager::GetWindow()
{
    return m_window;
}

void WindowManager::set_fullscreen(bool isFullSrn)
{

    if (isFullSrn) {

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        // Get the video mode of the monitor
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);
        glfwSetWindowMonitor(this->m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }  
};

int WindowManager::GetWindowWidth()
{
    return m_windowWidth;
};

int WindowManager::GetWindowHeight()
{
    return m_windowHeight;
};

// Function to update window size if it has changed (called every frame or when resizing)
void WindowManager::UpdateWindowSize()
{
    if (m_window != nullptr) {
        glfwGetFramebufferSize(m_window, &m_windowWidth, &m_windowHeight);
        glViewport(0, 0, m_windowWidth, m_windowHeight);

    }
}


void WindowManager::pre_render()
{
    glViewport(0, 0, m_windowWidth, m_windowWidth);

    // Set the background color
    glClearColor(0.247, 0.247, 0.247, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mUIx->pre_render();
};


void WindowManager::end()
{};

void WindowManager::render()
{

    mViewport->render();

    mUIx->render();

    this->UpdateWindowSize();

    // Handle Input here
    this->handleInputs();
};


void WindowManager::post_render()
{
    mUIx->post_render();
    glfwSwapBuffers(m_window);
    glfwPollEvents();
};

void WindowManager::Clean()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
bool WindowManager::isRunning()
{
    return !glfwWindowShouldClose(m_window);
};

double mouseX, mouseY;
void WindowManager::handleInputs() {
    // Retrieve current mouse position
    glfwGetCursorPos(this->GetWindow(), &mouseX, &mouseY);

    // Calculate mouse offsets
    float xOffset = static_cast<float>(mouseX - lastX);
    float yOffset = static_cast<float>(lastY - mouseY);  // Inverted Y-axis

    // Store current mouse position for next frame
    lastX = mouseX;
    lastY = mouseY;

    // Check if middle mouse button is pressed and control key is held for zooming
    if (input.isMousePressed(GLFW_MOUSE_BUTTON_MIDDLE)) {
        if (input.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
            mViewport->on_zoom(yOffset, 0.2f);
        }
        else {

            // Pass the mouse offsets to the viewport for orbiting
            mViewport->on_orbit(xOffset, yOffset, 0.6f, true);
        }
    };


    // Check for mouse click for selection (left mouse button)
    if (InputManager::getInstance().isMousePressed(GLFW_MOUSE_BUTTON_LEFT)) {
        // Pass the mouse position to the viewport for entity selection
        mViewport->on_mouse_click(static_cast<float>(mouseX), static_cast<float>(mouseY), this->GetWindow());
    }

    if (input.isKeyPressedDown(GLFW_KEY_X)) {
        mEntityHandler->TerminateEntity();
    }
};