#include "pch.h"
#include "mesh.h"

elems::Mesh::Mesh(PrimitiveType type)
{
    switch (type) {
    case PrimitiveType::Cube:
        mPrimitives->cube();
        break;
    case PrimitiveType::Plane:
        mPrimitives->plane();
        break;
    case PrimitiveType::Sphere:
        std::cerr << "PrimitiveType::Sphere is not yet implemented.\n";
        return;
    default:
        throw std::runtime_error("Unsupported PrimitiveType!");
    }
	mBuffer->create(mPrimitives->getVertices(), mPrimitives->getIndices());
};


void elems::Mesh::draw()
{
	//Bind and render
	mBuffer->bind();
	mBuffer->draw(GL_TRIANGLES);
	mBuffer->unbind();
};

