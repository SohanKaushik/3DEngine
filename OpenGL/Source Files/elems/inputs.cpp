#include "pch.h"

#include "elems/inputs.h"


InputManager& InputManager::getInstance() {
	static InputManager instance;
	return instance;
};

InputManager::InputManager() :
	window(nullptr), mouseX(0), mouseY(0) {};


void InputManager::Initialize(GLFWwindow* window)
{
	this->window = window;


	//Set GLFW callbacks
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		InputManager::getInstance().processKeyCallBack(key, scancode, action, mods);
		});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
		InputManager::getInstance().processMouseButtonCallBack(button, action, mods);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		InputManager::getInstance().processCursorPositionCallBack(xpos, ypos);
		});
};

// Checks if a specific key is pressed
bool InputManager::isKeyPressed(int key) {
	return keyStates[key];
};


// Checks if a specific mouse button is pressed
bool InputManager::isMousePressed(int button) {
	return mouseButtonStates[button];
};

void InputManager::getMousePosition(double& x, double& y) {
	x = mouseX;
	y = mouseY;
};

// Processes key events (key press/release)
void InputManager::processKeyCallBack(int key, int scancode, int action, int mods) {
	keyStates[key] = (action != GLFW_RELEASE);		             // If the action is not RELEASE, mark the key as pressed
};

// Processes mouse button events (button press/release)
void InputManager::processMouseButtonCallBack(int button, int action, int mods) {
	mouseButtonStates[button] = (action != GLFW_RELEASE);   	 // If the action is not RELEASE, mark the button as pressed
};

void InputManager::processCursorPositionCallBack(double xpos, double ypos) {
	mouseX = xpos;
	mouseY = ypos;
};
