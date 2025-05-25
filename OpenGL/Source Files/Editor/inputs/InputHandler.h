#pragma once
#include <unordered_map>

#include "pch.h"

namespace Inputs {

	class Inputs {

		void init(GLFWwindow* window);

        void onKeyPress(int key);
        void update();
	};
}