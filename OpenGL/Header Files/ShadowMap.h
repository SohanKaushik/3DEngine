#pragma once
#include <glad/glad.h>

class ShadowMap {


public:
	ShadowMap();
	~ShadowMap();


	virtual bool Init(unsigned int width, unsigned int height) ;
	virtual void Write();
	virtual void Read(GLenum textureInit);

	unsigned int GetShadowMap() const { return shadowMap; }
	unsigned int GetFBO() const { return FBO; }

	

protected:
	unsigned int FBO, shadowMap;
	unsigned int shadowWidth, shadowHeight;
};