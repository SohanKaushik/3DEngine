#include "pch.h"
#include "ui/viewport.h"

ui::Viewport::Viewport()
{
	std::cout << "Viewport constructor called" << std::endl;
	mShader->load("Resource Files/Shaders/default.vert", "Resource Files/Shaders/default.frag");
};

void ui::Viewport::render()
{	
	mShader->use();
	mGrid->render();
};

void ui::Viewport::destroy()
{
	mGrid->destroy();
};

