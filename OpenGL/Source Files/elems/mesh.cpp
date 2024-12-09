#include "pch.h"
#include "mesh.h"

elems::Mesh::Mesh(Transform transform) : transform()
{
	mPrimitives->cube();
	mBuffer->create(mPrimitives->getVertices(), mPrimitives->getIndices());
};


void elems::Mesh::draw()
{
	//for (auto& poly : primitives) {
	//	Primitive* primitive = poly.second;

	//	float angle = glfwGetTime() * 50.0f; // Rotate 50 degrees per second
	//	m_model = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

	//	mShader->SetUniformMat4f("model", m_model);
	//	mShader->SetUniform3fv("color", glm::vec3(1.0f, 0.0f, 0.0f));
	//	primitive->render();
	//}

	//Bind and render
	mBuffer->bind();
	mBuffer->draw(mPrimitives->getIndices().size());
	//mBuffer->unbind();

};

//void elems::Mesh::init()
//{
//	
//};

//void elems::Mesh::create_buffer()
//{
//
//}
//
//void elems::Mesh::unbind_buffer()
//{
//
//};
