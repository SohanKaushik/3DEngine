#include "pch.h"
#include "ShadowMap.h"


ShadowMap::ShadowMap() : FBO(0), shadowMap(0), shadowWidth(1024), shadowHeight(1024) {}

ShadowMap::~ShadowMap() {
	if (FBO) {
		glDeleteFramebuffers(1, &FBO);
	}
	if (shadowMap) {
		glDeleteTextures(1, &shadowMap);
	}
}


bool ShadowMap::Init(unsigned int width, unsigned int height) {

	shadowWidth = width;
	shadowHeight = height;

	glGenFramebuffers(1, &FBO);

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);

	//Allocating storage for depth texture
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		shadowWidth, shadowHeight, 0, 
		GL_DEPTH_COMPONENT, GL_FLOAT, nullptr
	);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if(status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer Error: %i\n" << status;
		return false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
};


void ShadowMap::Write() {
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void ShadowMap::Read(GLenum textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
}

