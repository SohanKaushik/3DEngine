#pragma once

namespace render {

	class ShadowMap {

	public:
		void create_buffer(int s_width, int s_height);
		void bind();
		void unbind();
		unsigned int get_dtexture();

	private:
		unsigned shadowbuffer, depth_texture, rbo;
		int m_height, m_widht;
	};
}