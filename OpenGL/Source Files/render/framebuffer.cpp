#include "framebuffer.h"

void render::DefualtFrameBuffer::create_buffer(int width, int height)
{
	m_widht = width;
	m_height = height;

	// Create framebuffer
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// Create a texture to store the rendered image
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// Create a renderbuffer object for depth and stencil attachments
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	// Check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "Error: Framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

};

void render::DefualtFrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, m_widht, m_height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
};

void render::DefualtFrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

unsigned int render::DefualtFrameBuffer::getID()
{
	return framebuffer;
};

unsigned int render::DefualtFrameBuffer::get_texture()
{
	return texture; 
};



// Anti- Aliasing Frame-Buffer
void render::AntiAliasingFrameBuffer::create_buffer(int width, int height) {

	aa_widht = width;
	aa_height = height;
	int samples = 8;

	// Generating Anti- Alisaing Frame-Buffer
	glGenFramebuffers(1, &multisamplefbo);
	glBindFramebuffer(GL_FRAMEBUFFER, multisamplefbo);

	// Create a multisampled texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, width, height, GL_TRUE); 

	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture, 0);


	// Create a Multisampled Render-buffer-object
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR::FRAMEBUFFER:: Multisample framebuffer not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
};

void render::AntiAliasingFrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, multisamplefbo);  // Bind the MSAA framebuffer
	glViewport(0, 0, aa_widht, aa_height);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear color and depth buffers if needed
};


void render::AntiAliasingFrameBuffer::unbind() {
	glBindFramebuffer(GL_READ_FRAMEBUFFER, multisamplefbo);  // Read from MSAA framebuffer
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);  // Write to the default framebuffer (window)

	// Resolve MSAA texture to the default framebuffer
	glBlitFramebuffer(0, 0, aa_widht, aa_height, 0, 0, aa_widht, aa_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);  // Unbind MSAA framebuffer from GL_FRAMEBUFFER
};

unsigned int render::AntiAliasingFrameBuffer::getID() {
	return multisamplefbo;
};

unsigned int render::AntiAliasingFrameBuffer::get_texture()
{
	return texture;
};