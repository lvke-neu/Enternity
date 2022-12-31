#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

BEGIN_ENTERNITY
class Triangle
{
public:
	Triangle();
	void draw();
	~Triangle();
private:
	unsigned int vertexarray;
	VertexBuffer* vertexbuffer;
	IndexBuffer* indexbuffer;
	unsigned int program;
};
END_ENTERNITY