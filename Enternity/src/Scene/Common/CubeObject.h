#pragma once
#include "Transform.h"
#include "Material.h"

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Camera3D;
	class Light;
	class CubeObject
	{
	public:
		CubeObject(Camera3D* camera3D, Light* light);
		~CubeObject();
		void Draw();
		void RecompileShader();
		void RenderGUI();
	public:
		Transform m_transform;
	private:
		VertexArray* m_pVertexArray;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
		PhongMaterial m_material;
		Camera3D* m_pCamera3D;
		Light* m_pLight;
	};
}