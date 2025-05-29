#include <Engine/inputs/inputhandler.h>

using namespace Engine::Inputs;

std::unordered_map<int, bool> Input::keyStates;
std::unordered_map<int, bool> Input::mouseStates;
std::unordered_map<int, bool> Input::keyDownFlags;

double Input::_x = 0.0;
double Input::_y = 0.0;

void Engine::Inputs::Input::initialize(GLFWwindow* window)
{
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseCallback);
	glfwSetCursorPosCallback(window, CursorCallback);
}

// actions
bool Input::isKeyPressed(KeyCode key) {
	return keyStates[static_cast<int>(key)];
}
bool Input::isMousePressed(MouseCode button) {
	return mouseStates[static_cast<int>(button)];
}
bool Input::isKeyPressedDown(KeyCode key) {
	int code = static_cast<int>(key);

	if (keyStates[code] && !keyDownFlags[code]) {
		keyDownFlags[code] = true;  // mark it as "already pressed"
		return true;
	}
	return false;
}

// callbacks
void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) keyStates[key] = true;
	else if (action == GLFW_RELEASE) {
		keyStates[key] = false; keyDownFlags[key] = false;
	}
}

void Engine::Inputs::Input::MouseCallback(GLFWwindow* window, int button, int action, int mods){
	if (action == GLFW_PRESS) mouseStates[button] = true;
	else if (action == GLFW_RELEASE) mouseStates[button] = false;
}

void Engine::Inputs::Input::CursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	_x = xpos;
	_y = ypos;
}

