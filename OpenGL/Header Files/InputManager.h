#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputManager
{
public:
	
	static InputManager& getInstance();

	InputManager();

	void Initialize(GLFWwindow* window);
	bool isKeyPressed(int key);
	bool isMousePressed(int button);
	void getMousePosition(double& x, double& y);

	void processKeyCallBack(int key, int scancode, int action, int mods);
	void processMouseButtonCallBack(int button, int action, int mods);
	void processCursorPositionCallBack(double xPos, double yPos);
	     
private:

	GLFWwindow* window;
	std::unordered_map<int, bool> keyStates;
	std::unordered_map<int, bool> mouseButtonStates;
	double mouseX, mouseY;


	// Delete copy constructor and assignment operator
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
};

