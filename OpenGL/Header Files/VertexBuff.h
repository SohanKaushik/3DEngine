#pragma once


class VertexBuff {

private:	
	unsigned int  ID;   //unique id for opengl bufferws

public:
	VertexBuff(const void* data, unsigned int size);
	~VertexBuff();


	void Bind() const;
	void Unbind() const;

};