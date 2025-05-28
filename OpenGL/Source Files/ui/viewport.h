#pragma once
#include "pch.h"

#include "ui/grid.h"
#include "elems/Mesh.h"
#include "elems/light.h"
//#include "elems/camera.h"
#include "elems/entity.h"
#include "shader/shader.h"

#include "render/ShadowMap.h"
#include <Editor/selection.h>
#include "render/framebuffer.h"
#include "Editor/EditorCamera.h"
#include "Editor/EntityHandler.h"

namespace ui {
	
	class Viewport {

	public:

		void Init();
		void render();

		void destroy();

		void on_orbit(float xOffset, float yOffset, float speed, bool constraint);
		void on_zoom(float offset, float senst);
		void on_mouse_click(double mouse_x, double mouse_y, GLFWwindow* window) {};

		void RenderSceneUI();

		Editor::Entity& def_enit();


	private:
		double lastX = 400.0, lastY = 300.0; // Default mouse position
		glm::vec2 m_size;

		std::unique_ptr<ui::Grid> mGrid = std::make_unique<ui::Grid>();

		std::unique_ptr<Shader[]> mShader = std::make_unique<Shader[]>(5);
		std::unique_ptr<Editor::Camera> mCamera;
		

		// Frame-Buffers
		std::unique_ptr<render::DefualtFrameBuffer> mFramebuffer = std::make_unique<render::DefualtFrameBuffer>();
		//std::unique_ptr<Editor::Selection> _selection;

	};
}
