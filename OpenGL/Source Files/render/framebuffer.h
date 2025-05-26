#pragma once
#include "pch.h"
#include "elems/camera.h"


namespace render {

	class Framebuffer {

	public:

		virtual void create_buffer(int width, int height) = 0;
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual unsigned int get_texture() = 0;
		virtual unsigned int getID() = 0;
		//virtual void create_multisample_buffer(int width, int height, int samples) = 0;

	};


	class DefualtFrameBuffer : Framebuffer {

	public:
		void create_buffer(int width, int height) override;
		void bind() override;
		void unbind() override;

		unsigned int getID() override;
		unsigned int get_texture() override;

	private:
		unsigned framebuffer, texture, rbo;
		int m_height, m_width = 0;
	};

	class AntiAliasingFrameBuffer : Framebuffer {

	public:
		void create_buffer(int width, int height) override;
		void bind() override;
		void unbind() override;
		unsigned int get_texture() override;
		unsigned int getID() override;

	private:

		unsigned multisamplefbo, texture, rbo;
		int aa_height, aa_widht;
	};

	class PickingFramebuffer : Framebuffer {

	public:
		void create_buffer(int width, int height) override;
		void bind() override;
		void unbind() override;
		unsigned int get_texture() override;
		unsigned int getID() override;

	private:
		unsigned int picking_fbo, color_texture, depth_rbo;
		int _height, _width;
	};
	/*class CameraUniformFrameBuffer : Framebuffer {

	public:

		void create_buffer(const elems::CameraUniforms& uniforms);
		void update_buffer(const elems::CameraUniforms& uniforms);
		void bind() override;
		void unbind() override;

	private:

		unsigned cameraUBO, m_texture, m_ubo;
		int ubo_width, ubo_height;
	};*/

};