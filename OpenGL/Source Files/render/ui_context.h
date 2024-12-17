#pragma once
#include "pch.h"
#include "elems/mesh.h"

namespace render {

	class UIXContext {

	public:
		void init(GLFWwindow* window);
		void pre_render();
		void render();
		void post_render();
		void end();

	private:
		void render_toolbar();
		void render_inspector();
		void render_hierarchy();
		void render_assets_hierarchy();

	private:

		void ShowFileMenu();
		void ShowSimpleFileMenu();
		void ShowEditMenu();
		void ShowAddMenu();

	private:
		std::unique_ptr<elems::Mesh> mMesh;
	};
}