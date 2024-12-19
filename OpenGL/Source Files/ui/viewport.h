#pragma once
#include "pch.h"

#include "elems/camera.h"
#include "elems/light.h"
#include "shader/shader.h"
#include "elems/inputs.h"
#include "ui/grid.h"
#include "elems/Mesh.h"
#include "elems/entity.h"
#include "render/framebuffer.h"

namespace ui {

	class Viewport {

	public:

		/*static Viewport& getInstance() {
			static Viewport instance;
			return instance;
		};

		Viewport() {}*/

		void Init();
		void render();

		void destroy();

		void on_orbit(float xOffset, float yOffset, float speed, bool constraint);
		void on_zoom(float offset, float senst);

		void RenderSceneUI();


		void AddEntities();
		void RenderEntities();

		void AddEntity(elems::EntityType type);
		void GetViewport();

	private:
		double lastX = 400.0, lastY = 300.0; // Default mouse position
		glm::vec2 m_size;

		std::unique_ptr<ui::Grid> mGrid = std::make_unique<ui::Grid>();

		std::unique_ptr<Shader[]> mShader = std::make_unique<Shader[]>(5);
		std::unique_ptr<elems::Camera> mCamera;
		std::unique_ptr<render::Framebuffer> mFramebuffer = std::make_unique<render::Framebuffer>();

		std::vector<std::shared_ptr<elems::Entity>> mEntity;
		//std::unique_ptr<elems::DirectionalLight> mLight;

		/*Viewport(const Viewport&) = delete;
		Viewport& operator=(const Viewport&) = delete;*/
	};
}
