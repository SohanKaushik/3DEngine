#pragma once
#include "pch.h"

#include "elems/camera.h"
//#include "elems/mesh.h"
#include "elems/light.h"
#include "shader/shader.h"
#include "elems/inputs.h"
#include "ui/grid.h"
#include "elems/Mesh.h"


namespace ui {

	class Viewport {

	public:

		void Init();
		void render();

		void destroy();


	private:
	

		std::unique_ptr<ui::Grid> mGrid = std::make_unique<ui::Grid>();
		std::unordered_map<std::string, elems::Mesh*> mMesh;

		std::unique_ptr<Shader> mShader = std::make_unique<Shader>();
		std::unique_ptr<elems::Camera> mCamera;
		
	};
}
