#pragma once
#include "pch.h"
#include "elems/mesh.h"
#include "Editor/EntityHandler.h"
#include "Editor/core/render_image.h"

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
		void lights();
		void materials();

	private:

		void ShowFileMenu();
		void ShowEditMenu();
		void ShowAddMenu();

	private:
		std::unique_ptr<core::RenderImage> rendr_image = std::make_unique<core::RenderImage>();

		std::unique_ptr<render::PickingFramebuffer> _selection_texture = std::make_unique<render::PickingFramebuffer>();

	};
}