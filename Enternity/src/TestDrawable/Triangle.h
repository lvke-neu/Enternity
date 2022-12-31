#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

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
	Shader* shader;
};
END_ENTERNITY