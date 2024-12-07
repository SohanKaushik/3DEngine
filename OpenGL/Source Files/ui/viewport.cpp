#include "pch.h"
#include "ui/viewport.h"


void ui::Viewport::Init()
{
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

