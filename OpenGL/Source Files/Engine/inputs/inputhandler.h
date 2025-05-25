#pragma once
#include "pch.h"
#include <window/window.h>

namespace Engine {

	namespace Inputs {

		class Input {

			private:
				static std::unordered_map<int, bool> keyStates;
				static std::unordered_map<int, bool> mouseStates;

			public:
				static void initialize(GLFWwindow* window);
				static bool isKeyPressed(int key);
				static bool isMousePressed(int button);

			public:
				static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void MouseCallback(GLFWwindow* window, int key, int action, int mods);

		};
	}
}