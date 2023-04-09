#pragma once

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Camera3D;
	class TextureCube;
	class SkyboxObject
	{
	public:
		SkyboxObject(Camera3D* camera3D);
		~SkyboxObject();
		void Draw();
		void RecompileShader();
		void RenderGUI();

	private:
		VertexArray* m_pVertexArray;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
		Camera3D* m_pCamera3D;
		TextureCube* m_pTextureCube;
	};
}