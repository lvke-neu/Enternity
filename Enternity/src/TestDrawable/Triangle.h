#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"

BEGIN_ENTERNITY
class Triangle
{
public:
	Triangle();
	void draw();
	~Triangle();
private:
	VertexArray* vertexArray;
	VertexBuffer* vertexbuffer;
	IndexBuffer* indexbuffer;
	unsigned int program;
};
END_ENTERNITY