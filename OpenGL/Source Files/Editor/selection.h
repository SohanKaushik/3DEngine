#pragma once

#include "pch.h"
#include "shader/shader.h"

#include "EntityHandler.h"
#include "render/framebuffer.h"
#include <render/framebuffer_handler.h>

using namespace render;

namespace Editor {
	class Selection {


		//// Convert picking ID to RGB color (0.0 to 1.0)
		//glm::vec3 IDtoColor() {
		//	return glm::vec3(
		//		((ID >> 0) & 0xFF) / 255.0f,
		//		((ID >> 8) & 0xFF) / 255.0f,
		//		((ID >> 16) & 0xFF) / 255.0f
		//	);
		//}

		// Convert RGB color back to ID (0-255 values)
		static uint32_t ColorToID(unsigned char r, unsigned char g, unsigned char b) {
			return r + (g << 8) + (b << 16);
		}

	public:
		Selection() {
			int _store = FrameBufferHandle::AddFrameBuffer(
				std::unique_ptr<Framebuffer>(static_cast<Framebuffer*>(_buffer.release())),
				render::FrameBufferHandle::FrameBufferType::Color, "_Picking", 500, 500);

			_shader.load("Source Files/Editor/shaders/picking.vert", "Source Files/Editor/shaders/picking.frag");
		}

		void render() {
			FrameBufferHandle::RetrieveFrameBuffer(_store)->bind();
			Editor::EntityHandler::render(_shader);
			FrameBufferHandle::RetrieveFrameBuffer(_store)->unbind();
		}
		
		
	private:
		Shader _shader;
		int _store;
		std::unique_ptr<render::PickingFramebuffer> _buffer = std::make_unique<render::PickingFramebuffer>();
	};
}
