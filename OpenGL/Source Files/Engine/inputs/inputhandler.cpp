#include <Engine/inputs/inputhandler.h>

using namespace Engine::Inputs;

std::unordered_map<int, bool> Input::keyStates;
std::unordered_map<int, bool> Input::mouseStates;
std::unordered_map<int, bool> Input::keyDownFlags;


void Engine::Inputs::Input::initialize(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseCallback);
}

bool Input::isKeyPressed(KeyCode key) {
	return keyStates[static_cast<int>(key)];
}
bool Input::isMousePressed(MouseCode button) {
	return mouseStates[static_cast<int>(button)];
}
bool Input::isKeyPressedDown(KeyCode key) {
	int _key = static_cast<int>(key);
	if (keyStates[_key] && !keyDownFlags[_key]) {
		keyDownFlags[_key] = true;  // mark it as "already handled"
		return true;
	}
	return false;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) keyStates[key] = true;
	else if (action == GLFW_RELEASE) keyStates[key] = false;
}

void Engine::Inputs::Input::MouseCallback(GLFWwindow* window, int button, int action, int mods){
	if (action == GLFW_PRESS) mouseStates[button] = true;
	else if (action == GLFW_RELEASE) mouseStates[button] = false;
}

