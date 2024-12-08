#pragma once

#include "elems/Camera.h"
//#include "elems/mesh.h"
#include "elems/light.h"
#include "shader/shader.h"
//#include "render/opengl_buffer_manager.h"
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
		std::unique_ptr<ui::Grid> mGrid = std::make_unique<ui::Grid>();
		std::unique_ptr<Shader> mShader = std::make_unique<Shader>();
		std::unordered_map<std::string, elems::Primitive*> primitives; 
	};
}
