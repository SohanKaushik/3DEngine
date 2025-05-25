#pragma once
#include "pch.h"
#include <window/window.h>
#include <Engine/inputs/keycodes.h>
#include <Engine/inputs/mousecodes.h>

namespace Engine {

	namespace Inputs {

		class Input {
			
			private:
				static std::unordered_map<int, bool> keyStates;
				static std::unordered_map<int, bool> mouseStates;
				static std::unordered_map<int, bool> keyDownFlags;

			public:
				static void initialize(GLFWwindow* window);
				static bool isKeyPressed(KeyCode key);
				static bool isKeyPressedDown(KeyCode key);
				static bool isMousePressed(MouseCode button);

			private:
				static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
				static void CursorCallback(GLFWwindow* window, double xpos, double ypos);

			public:
				static glm::vec2 GetMousePosition() { return glm::vec2(_x, _y); }

			private:
				static double _x;
				static double _y;

		};
	}
}