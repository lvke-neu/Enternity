#pragma once

#include "Interface/SceneInterface.h"

namespace Enternity
{
	class VertexArray;
	class IndexBuffer;
	class Shader;
	class Texture2D;
	class TextureMapScene : public IScene
	{
	public:
		virtual void Initialize() override;
		virtual void Finalize() override;
		virtual void Tick(float deltaTime) override;
		virtual void RecompileShader() override;
	private:
		VertexArray* m_pVertexArray;
		IndexBuffer* m_pIndexBuffer;
		Shader* m_pShader;
		Texture2D* m_pTexture;
	};
}