#include "pch.h"
#include "mesh.h"

elems::Mesh::Mesh(Transform transform) : transform()
{
	this->setPosition(transform.position);
	this->setRotation(transform.rotation);
	this->setScale(transform.scale);

	mPrimitives->cube();
	mBuffer->create(mPrimitives->getVertices(), mPrimitives->getIndices());
};


void elems::Mesh::draw()
{
	//Bind and render
	mBuffer->bind();
	mBuffer->draw(GL_TRIANGLES);
	mBuffer->unbind();
};

