#pragma once
#include "pch.h"

#include "elems/camera.h"
//#include "elems/mesh.h"
#include "elems/light.h"
#include "shader/shader.h"
#include "elems/inputs.h"
#include "ui/grid.h"
#include "Object.h"
#include "elems/Primitive.h"


namespace ui {

	class Viewport {

	public:

		void Init();
		void render();

		void destroy();


	private:
		glm::mat4 m_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		std::unique_ptr<ui::Grid> mGrid = std::make_unique<ui::Grid>();
		std::unique_ptr<Shader> mShader = std::make_unique<Shader>();
		std::unique_ptr<elems::Camera> mCamera;
		std::unordered_map<std::string, elems::Primitive*> primitives; 
	};
}
