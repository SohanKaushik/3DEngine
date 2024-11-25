#pragma once
#include <glad/glad.h>

class ShadowMap {


public:
	ShadowMap();

	virtual bool Init(unsigned int width, unsigned int height) ;
	virtual void Write();
	virtual void Read(GLenum textureInit);

	unsigned int  GetShadowWidth() { return shadowWidth; }
	unsigned int  GetShadowHeight() { return shadowHeight; }


protected:
	unsigned int FBO, shadowMap;
	unsigned int shadowWidth, shadowHeight;
};