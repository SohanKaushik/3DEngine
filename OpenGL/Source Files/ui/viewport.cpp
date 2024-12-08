#include "pch.h"
#include "ui/viewport.h"
#include "Object.h"
using namespace elems;

void ui::Viewport::Init()
{
	std::cout << "Viewport Initialization" << std::endl;
	mShader->load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");

	primitives["cube1"] = new Primitive("cube1");
};

void ui::Viewport::render()
{	

	mShader->use();

	for (auto& poly : primitives) {
		Primitive* primitive = poly.second;
		//mShader->SetUniformMat4f("model", primitive->transform.getMatrix());
		mShader->SetUniform3fv("color", glm::vec3(1.0f, 0.0f, 0.0f));
		primitive->render();
	}

	//mGrid->render();
}




void ui::Viewport::destroy()
{
	mGrid->destroy();
};

