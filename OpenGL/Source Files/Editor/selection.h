#pragma once

#include "pch.h"
#include "shader/shader.h"

#include "EntityHandler.h"
#include "render/framebuffer.h"
#include <render/framebuffer_handler.h>


using namespace render;

namespace Editor {
	class Selection {


		// Convert picking ID to RGB color (0.0 to 1.0)
		glm::vec3 IDtoColor() {

			int _id = EntityHandler::GetID();

			return glm::vec3(
				((_id >> 0) & 0xFF) / 255.0f,
				((_id >> 8) & 0xFF) / 255.0f,
				((_id >> 16) & 0xFF) / 255.0f
			);
		}

		// Convert RGB color back to ID (0-255 values)
		static uint32_t ColorToID(unsigned char r, unsigned char g, unsigned char b) {
			return r + (g << 8) + (b << 16);
		}

	public:
		Selection() {
			_store = FrameBufferHandle::AddFrameBuffer(
				std::move(_buffer),
				render::FrameBufferHandle::FrameBufferType::Color, "_Picking", 200, 200);

			_shader.load("Source Files/Editor/shaders/picking.vert", "Source Files/Editor/shaders/picking.frag");
		}

		void render() {

			/*if (Engine::Inputs::Input::isKeyPressed(Engine::Inputs::KeyCode::Space)) {

			}*/
			_shader.use();
			//_shader.SetUniform1i("_colorcode", );
			FrameBufferHandle::RetrieveFrameBuffer(_store)->bind();
			Editor::EntityHandler::render(_shader);
			FrameBufferHandle::RetrieveFrameBuffer(_store)->unbind();
		}

		void _readpix() {

		}

	private:
		Shader _shader;
		int _store;
		std::unique_ptr<render::PickingFramebuffer> _buffer = std::make_unique<render::PickingFramebuffer>();
	};
}
