#pragma once
#include "Interface/SceneInterface.h"
#include "Core/Math/Matrix.h"
#include "Core/Math/Vector.h"

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Texture2D;
	class TextureMapScene : public IScene
	{
		friend class GUIRender;
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void Tick(float deltaTime) override;
		virtual void RecompileShader() override;
		virtual void RenderGUI() override;
	private:
		VertexArray* m_pVertexArray;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
		Texture2D* m_pTexture;
		Matrix4x4f m_mvp;
		Vector3f m_translation = {0.0f, 0.0f, 0.0f};
		Vector3f m_rotation = { 0.0f, 0.0f, 0.0f };
		Vector3f m_scale = {1.0f, 1.0f, 1.0f};
	};
}