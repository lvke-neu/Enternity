#pragma once
#include "Transform.h"

namespace Enternity
{
	class Camera3D;
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Light
	{
	public:
		Light(Camera3D* camera3D);
		~Light();
		void Draw();
		Transform m_transform;
	private:
		VertexArray* m_pVertexArray;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
		Camera3D* m_pCamera3D;
	};
}