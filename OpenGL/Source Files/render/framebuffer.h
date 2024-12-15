#pragma once
#include "pch.h"

namespace render {

	class Framebuffer {

	public:

		void create_buffer(int width, int height);
		void bind();
		void unbind();
		unsigned int get_texture();

	private:
		unsigned framebuffer, texture, rbo;
		int m_height, m_widht;
	};
};