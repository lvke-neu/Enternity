#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Transform/Transform.h"

BEGIN_ENTERNITY
class Triangle
{
public:
	Triangle();
	void draw();
	~Triangle();
private:
	void operationScene();
private:
	VertexArray* vertexArray;
	VertexBuffer* vertexbuffer;
	IndexBuffer* indexbuffer;
	Shader* shader;
	Texture* texture;

	Transform m_Transform;
};
END_ENTERNITY