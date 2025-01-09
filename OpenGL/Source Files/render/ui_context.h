#pragma once
#include "pch.h"
#include "elems/mesh.h"
#include "ui/viewport.h"
#include "Editor/EntityHandler.h"

namespace render {

	class UIXContext {

	public:
		
		void init(GLFWwindow* window, ui::Viewport* viewport);
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
		void ShowEditMenu();
		void ShowAddMenu();

	private:
		std::shared_ptr<Editor::EntityHandler> mEntityHandler = Editor::EntityHandler::GetInstance(); 
		ui::Viewport* mViewport = nullptr;
	};
}