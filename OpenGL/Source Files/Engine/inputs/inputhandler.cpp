#include <Engine/inputs/inputhandler.h>

using namespace Engine::Inputs;

std::unordered_map<int, bool> Input::keyStates;
std::unordered_map<int, bool> Input::mouseStates;

void Engine::Inputs::Input::initialize(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseCallback);
}

bool Input::isKeyPressed(int key) {
	return keyStates[key];
}
bool Input::isMousePressed(int button) {
	return mouseStates[button];
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) keyStates[key] = true;
	else if (action == GLFW_RELEASE) keyStates[key] = false;
}

void Engine::Inputs::Input::MouseCallback(GLFWwindow* window, int button, int action, int mods){
	if (action == GLFW_PRESS) mouseStates[button] = true;
	else if (action == GLFW_RELEASE) mouseStates[button] = false;
}

