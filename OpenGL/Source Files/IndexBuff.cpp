#include "IndexBuff.h"
#include <glad/glad.h>
#include <assert.h>

#define ASSERT(x) assert(x)

IndexBuff::IndexBuff(const unsigned int* data, unsigned int count) 
	: m_Count(count)
{

	//ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}


IndexBuff::~IndexBuff() {
	glDeleteBuffers(1, &ID);			//Free GPU memory
}

void IndexBuff::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);     // // Bind this buffer
}

void IndexBuff::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);           // Unbind the buffer (make none active) 0
}