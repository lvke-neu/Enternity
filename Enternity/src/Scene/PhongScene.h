#pragma once
#include "Interface/SceneInterface.h"
#include "Common/Transform.h"

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Texture2D;
	class Camera3D;
	class CameraController;
	class Light;
	class PhongScene : public IScene
	{
		friend class GUIRender;
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void Tick(float deltaTime) override;
		virtual void RecompileShader() override;
		virtual void RenderGUI() override;
		virtual void OnResize(int width, int height) override;
	private:
		VertexArray* m_pVertexArray;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
		Texture2D* m_pTexture;
		Camera3D* m_pCamera3D;
		CameraController* m_pCameraController;
		Transform m_transform;
		Light* m_light;
	};
}