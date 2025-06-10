#include "pch.h"
#include "Selection.h"

using namespace render;
using namespace Engine::Inputs;

namespace Editor {


	Selection::Selection() {
		_buffer = std::make_unique<render::PickingFramebuffer>();

		_store = FrameBufferHandle::AddFrameBuffer(
			std::move(_buffer),
			render::FrameBufferHandle::FrameBufferType::Color, "_Picking", 200, 200);
		_shader[0].load("Source Files/Editor/shaders/picking.vert", "Source Files/Editor/shaders/picking.frag");
		_shader[1].load("Source Files/Editor/shaders/outline.vert", "Source Files/Editor/shaders/outline.frag");
	}

	uint32_t Selection::DecodeColorToID(unsigned char r, unsigned char g, unsigned char b) {
		uint32_t id =  r + (g << 8) + (b << 16);
		if (id >= EntityHandler::GetID()) {
			return -1;
		}
		return id;
	}
	
	bool Selection::isSelected() {

		float scaleX = 200 / (float)457;
		float scaleY = 200 / (float)602;

		float offsety = 5;
		float offsetx = 25;

		GLubyte pixel[4];
		int x = static_cast<int>(_mouseloc.x * scaleX);
		int y = static_cast<int>(_mouseloc.y * scaleY);

		int flippedY = 200 - 1 - y;
		glReadPixels(x, flippedY - 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

		// Decode the color back into an ID
		pickedID = DecodeColorToID(pixel[0], pixel[1], pixel[2]);
		if (pickedID == -1) {
			std::cout << _mouseloc.x << std::endl;
			return false;
		}
		return true;
	}

	void Selection::render(Editor::Camera* camera) {

		_mouseloc = Input::GetMousePosition();

		_shader[0].use();
		FrameBufferHandle::RetrieveFrameBuffer(_store)->bind();


		camera->UpdateCameraMatrix(_shader[0]);
		for (uint32_t i = 0; i < EntityHandler::GetID(); i++) {
			_shader[0].SetUniform1i("_id", i);
			Editor::EntityHandler::render(_shader[0], i);
		}


		if (Input::isMousePressedDown(MouseCode::Left) && _mouseloc.x < 443) {
			if (!isSelected()) {
				EntityHandler::SetSelectedEntity(-1);
				return;
			}
			EntityHandler::SetSelectedEntity(pickedID);
		}

		FrameBufferHandle::RetrieveFrameBuffer(_store)->unbind();

	}


	void Selection::highlight(Editor::Camera* camera)
	{
		glStencilMask(0x00);

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glDisable(GL_DEPTH_TEST);


		_shader[1].use();
		camera->UpdateCameraMatrix(_shader[1]);
		EntityHandler::render(_shader[1], pickedID);

		glStencilMask(0xFF);
		glStencilFunc(GL_ALWAYS, 0, 0xFF);
		glEnable(GL_DEPTH_TEST);
	}

}
