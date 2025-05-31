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

	uint32_t Selection::ColorToID(unsigned char r, unsigned char g, unsigned char b) {
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

		_id = (uint32_t)EntityHandler::GetID();

		_shader.use();
		FrameBufferHandle::RetrieveFrameBuffer(_store)->bind();
		camera->UpdateCameraMatrix(_shader);


	/*	for (int i = 0; i < _id; i++) {
			glm::vec3 color = IDtoColor(i);
		}*/

			Editor::EntityHandler::render(_shader);
			//renderbyID(_shader, _id);
		FrameBufferHandle::RetrieveFrameBuffer(_store)->unbind();

		_readpix();
	}

	void Selection::_readpix() {
		_mouseloc = Input::GetMousePosition();

		if (Input::isMousePressedDown(MouseCode::Left)) {
			std::cout << glm::to_string(_mouseloc) << std::endl;
		}
		GLubyte pixel[4];
		glReadPixels(_mouseloc.x, _mouseloc.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
	}

	// | STENCIL BUFFER |
	void Selection::_writepix() {
		glm::vec3 color = IDtoColor(_id);
	}

	void Selection::renderbyID(Shader& shader, uint32_t id)
	{
		auto entity = EntityHandler::GetSelectedEntityById(id);
		auto mesh = entity->GetComponent<Editor::MeshComponent>();

		mesh->SetMaterial(glm::vec3(1.0, 0.0, 0.0));  // hardcore values for debug purposes
		glm::vec3& color = mesh->GetColor();

		std::cout << glm::to_string(color);
	}
}
