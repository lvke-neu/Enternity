#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Transform/Transform.h"

BEGIN_ENTERNITY
class LightObject
{
public:
	LightObject();
	void draw();
	~LightObject();
public:
	Transform& GetTransform()
	{
		return m_Transform;
	}
private:
	void operationScene();
private:
	VertexArray* vertexArray;
	VertexBuffer* vertexbuffer;
	IndexBuffer* indexbuffer;
	Shader* shader;

	Transform m_Transform;
};
END_ENTERNITY