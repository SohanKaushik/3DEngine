#include "pch.h"
#include "Selection.h"

using namespace render;
using namespace Engine::Inputs;

namespace Editor {

	glm::vec3 Selection::IDtoColor(uint32_t id) {
		return glm::vec3(
			((id >> 0) & 0xFF) / 255.0f,
			((id >> 8) & 0xFF) / 255.0f,
			((id >> 16) & 0xFF) / 255.0f
		);
	}

	uint32_t Selection::DecodeColorToID(unsigned char r, unsigned char g, unsigned char b) {
		return r + (g << 8) + (b << 16);
	}

	Selection::Selection() {
		_buffer = std::make_unique<render::PickingFramebuffer>();

		_store = FrameBufferHandle::AddFrameBuffer(
			std::move(_buffer),
			render::FrameBufferHandle::FrameBufferType::Color, "_Picking", 200, 200);
		_shader.load("Source Files/Editor/shaders/picking.vert", "Source Files/Editor/shaders/picking.frag");
	}

	void Selection::render(Editor::Camera* camera) {


		_shader.use();
		FrameBufferHandle::RetrieveFrameBuffer(_store)->bind();


		camera->UpdateCameraMatrix(_shader);
		for (uint32_t i = 0; i < EntityHandler::GetID(); i++) {
			_shader.SetUniform1i("_id", i);
			Editor::EntityHandler::render(_shader, i);
		}



		FrameBufferHandle::RetrieveFrameBuffer(_store)->unbind();

		if (Input::isMousePressedDown(MouseCode::Left)) {
			std::cout << glm::to_string(_mouseloc) << std::endl;
			_readpix();
		}
	}

	void Selection::_readpix() {
		_mouseloc = Input::GetMousePosition();

		float scaleX = 200 / (float)646;
		float scaleY = 200 / (float)500;

		int fbX = glm::clamp(int(_mouseloc.x * scaleX), 0, 200 - 1);
		int fbY = glm::clamp(int(_mouseloc.y * scaleY), 0, 200 - 1);


		GLubyte pixel[4];
		int flippedY = 200 - 1 - fbY;
		glReadPixels(fbX, flippedY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

		// Decode the color back into an ID
		int pickedID = DecodeColorToID(pixel[0], pixel[1], pixel[2]);

		std::cout << "Picked Entity ID: " << pickedID << std::endl;

	}

	// | STENCIL BUFFER |
	void Selection::_writepix() {
		glm::vec3 color = IDtoColor(_id);
	}


}
