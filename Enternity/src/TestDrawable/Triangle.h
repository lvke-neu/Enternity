#pragma once
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Transform/Transform.h"

BEGIN_ENTERNITY

class LightObject;
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
	Texture* texture2;

	glm::vec3 m_color{ 1.0f,1.0f,1.0f };
	bool m_useColor = true;

	Transform m_Transform;

	LightObject* m_light{ nullptr };
};
END_ENTERNITY