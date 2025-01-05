#pragma once
#include "pch.h"

#include "elems/camera.h"
#include "elems/light.h"
#include "shader/shader.h"
#include "elems/inputs.h"
#include "ui/grid.h"
#include "elems/Mesh.h"
#include "elems/entity.h"
#include "Editor/EditorCamera.h"
#include "render/framebuffer.h"
#include "render/ShadowMap.h"

#include "Editor/EntityHandler.h"


namespace ui {
	
	class Viewport {

	public:

		void Init();
		void render();

		void destroy();

		void on_orbit(float xOffset, float yOffset, float speed, bool constraint);
		void on_zoom(float offset, float senst);

		void RenderSceneUI();

		Editor::Entity& AddEntity();


	private:
		double lastX = 400.0, lastY = 300.0; // Default mouse position
		glm::vec2 m_size;

		std::unique_ptr<ui::Grid> mGrid = std::make_unique<ui::Grid>();

		std::unique_ptr<Shader[]> mShader = std::make_unique<Shader[]>(5);
		std::unique_ptr<Editor::Camera> mCamera;
	
		Editor::EntityHandler* m_entity = new Editor::EntityHandler();


		// Frame-Buffers
		std::unique_ptr<render::DefualtFrameBuffer> mFramebuffer = std::make_unique<render::DefualtFrameBuffer>();
		std::unique_ptr<render::AntiAliasingFrameBuffer> mMultiSampleFramebuffer = std::make_unique<render::AntiAliasingFrameBuffer>();

		std::unique_ptr<render::ShadowMap> mShadowFrameBuffer = std::make_unique<render::ShadowMap>();

	};
}
