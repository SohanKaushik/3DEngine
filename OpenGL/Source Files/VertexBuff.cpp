#include "pch.h"
#include "VertexBuff.h"




VertexBuff::VertexBuff(const void* data, unsigned int size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}


VertexBuff::~VertexBuff(){
	glDeleteBuffers(1, &ID);			//Free GPU memory
}

void VertexBuff::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);     // // Bind this buffer
}

void VertexBuff::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);           // Unbind the buffer (make none active)
}