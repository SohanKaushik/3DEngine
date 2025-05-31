#pragma once

#include "shader/shader.h"
#include "EntityHandler.h"

#include "render/framebuffer.h"
#include <render/framebuffer_handler.h>
#include <Engine/inputs/inputhandler.h>

namespace Editor {
	class Selection {
	public:
		Selection();
		void render(Editor::Camera* camera);
		void read();
		void _writepix();

	private:
		static uint32_t DecodeColorToID(unsigned char r, unsigned char g, unsigned char b);

		uint32_t _id = 0;
		int _store = 0;
		Shader _shader;

		glm::vec2 _mouseloc = glm::vec2(0,0);
		std::unique_ptr<render::PickingFramebuffer> _buffer;
	};
}
