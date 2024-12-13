#pragma once
#include "pch.h"

namespace render {

	class UIXContext {

	public:
		void init(GLFWwindow* window);
		void pre_render();
		void render();
		void post_render();
		void end();
	};
}