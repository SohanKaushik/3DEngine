#include "pch.h"
#include "mesh.h"

elems::Mesh::Mesh(Transform transform) : transform()
{
	mPrimitives->cube();
	mBuffer->create(mPrimitives->getVertices(), mPrimitives->getIndices());
};


void elems::Mesh::draw()
{
	//Bind and render
	mBuffer->bind();
	mBuffer->draw(mPrimitives->getIndices().size());
	mBuffer->unbind();
};

