#pragma once

#include "pch.h"
#include "shader/shader.h"

#include "EntityHandler.h"
#include "render/framebuffer.h"

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

			std::cout << "hello i am from selection" << std::endl;
			//_buffer->create_buffer(500, 500);
			//_shader.load("Source Files/Editor/shaders/picking.vert", "Source Files/Editor/shaders/picking.frag");
		}

		void render() {

			//Editor::EntityHandler::GetInstance()->render(_shader);
			//_buffer->unbind();
		}

	private:
		Shader _shader;
		std::unique_ptr<render::PickingFramebuffer> _buffer = std::make_unique<render::PickingFramebuffer>();
	};
}
