#include "pch.h"
#include "mesh.h"
#include "shader/shader.h"

elems::Mesh::Mesh(PrimitiveType type)
{
    switch (type) {
    case PrimitiveType::cube:
        mPrimitives->cube();
        break;
    case PrimitiveType::plane:
        mPrimitives->plane();
        break;
    case PrimitiveType::sphere:
        std::cerr << "Sphere is not yet been implemented.\n";
        return;
    default:
        throw std::runtime_error("Unsupported PrimitiveType!");
    }
	mBuffer->create(mPrimitives->getVertices(), mPrimitives->getIndices());
};


void elems::Mesh::draw()
{
   // Shader mesh_shader;

	//Bind and render
	mBuffer->bind();
	mBuffer->draw(GL_TRIANGLES);
	mBuffer->unbind();
};

