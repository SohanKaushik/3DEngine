#include "pch.h"
#include "render/ShadowMap.h"

void render::ShadowMap::create_buffer(int s_width, int s_height)
{
    m_widht = s_width;
    m_height = s_height;

    // Create shadow framebuffer
    glGenFramebuffers(1, &shadowbuffer);


    // Create depth texture
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, s_width, s_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // Attach depth texture to framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, shadowbuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);
    glDrawBuffer(GL_NONE); // No color buffer
    glReadBuffer(GL_NONE); // No read buffer

    // Check framebuffer status
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "Error: Shadow map framebuffer is not complete! Status: " << status << std::endl;
    }

    // Unbind framebuffer and texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //  glBindTexture(GL_TEXTURE_2D, 0);
}

void render::ShadowMap::bind() {
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glBindFramebuffer(GL_FRAMEBUFFER, shadowbuffer); // Bind the shadow map framebuffer
    glViewport(0, 0, m_widht, m_height); // Set the viewport to match shadow map size
    glClear(GL_DEPTH_BUFFER_BIT); // Clear depth buffer before rendering
}

unsigned int render::ShadowMap::get_dtexture() {
    return depth_texture; // Return depth texture for use in shaders
}

void render::ShadowMap::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind the framebuffer
}
