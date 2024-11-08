#pragma once
#include <glad/glad.h>

#include <IndexBuff.h>
#include <VertexBuff.h>
#include <Shader.h>

class Rend {

public:
	void Draw(const VertexBuff& va, const IndexBuff& iv, const Shader& shader) const;
	void Clear() const;
};