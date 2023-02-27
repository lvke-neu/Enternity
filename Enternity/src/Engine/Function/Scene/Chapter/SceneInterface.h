#pragma once
#include "Function/Render/Wrapper/RenderWrapper.h"

namespace Enternity
{
	class Camera3D;
	class IScene
	{
	public:
		IScene();
		virtual ~IScene();
		virtual void tick(float deltaTime) = 0;
	protected:
		Camera3D* m_camera3D{ nullptr };
		VertexBuffer* m_vertexBuffer{ nullptr };
		IndexBuffer* m_indexBuffer{ nullptr };
		VertexArray* m_vertexArray{ nullptr };
		Shader* m_shader{ nullptr };
	};
}