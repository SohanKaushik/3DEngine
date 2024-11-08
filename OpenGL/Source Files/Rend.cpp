#include "Rend.h"





void Rend::Clear() const {

	// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  //bg color
	glClear(GL_COLOR_BUFFER_BIT);

};

void Rend::Draw(const VertexBuff& va, const IndexBuff& iv, const Shader& shader) const {

	shader.Bind();
	iv.Bind();
	va.Bind();


	glDrawElements(GL_TRIANGLES, iv.GetCount() , GL_UNSIGNED_INT, 0);
};