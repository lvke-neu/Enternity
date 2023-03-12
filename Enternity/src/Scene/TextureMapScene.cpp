#include "TextureMapScene.h"
#include "Core/Reflection/Reflection.h"
#include "Core/Blob/Blob.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Log/Log.h"
#include "Common/Vertex.h"
#include "RHI/VertexBuffer.h"
#include "RHI/VertexArray.h"
#include "RHI/IndexBuffer.h"
#include "RHI/Shader.h"
#include "RHI/Texture.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"
#include <glad/glad.h>

namespace Enternity
{
	REGISTER_CLASS(IScene, "TextureMapScene", TextureMapScene);

	void TextureMapScene::Initialize()
	{
		if (m_bIsInit)
			return;

		{
			VertexBuffer tmpVertexBuffer;
			std::vector<VertexPosColorNormalTexcoord> vertices;
			vertices.resize(4);

			vertices[0].position = Vector3f(-0.5f, 0.5f, 0.0f);
			vertices[1].position = Vector3f(0.5f, 0.5f, 0.0f);
			vertices[2].position = Vector3f(0.5f, -0.5f, 0.0f);
			vertices[3].position = Vector3f(-0.5f, -0.5f, 0.0f);
			
			vertices[0].color = Vector3f(1.0f, 0.0f, 0.0f);
			vertices[1].color = Vector3f(0.0f, 1.0f, 0.0f);
			vertices[2].color = Vector3f(0.0f, 0.0f, 1.0f);
			vertices[3].color = Vector3f(0.3f, 0.4f, 0.5f);

			vertices[0].texcoord = Vector2f(0.0f, 1.0f);
			vertices[1].texcoord = Vector2f(1.0f, 1.0f);
			vertices[2].texcoord = Vector2f(1.0f, 0.0f);
			vertices[3].texcoord = Vector2f(0.0f, 0.0f);

			Blob blob(vertices.size() * sizeof(VertexPosColorNormalTexcoord));
			blob.copyDataFrom(vertices.data());

			tmpVertexBuffer.init(&blob);

			m_pVertexArray = new VertexArray;
			m_pVertexArray->init(&tmpVertexBuffer, &VertexPosColorNormalTexcoord::vertexBufferLayout);
		}

		{
			std::vector<unsigned int> indices{ 3, 1, 0, 3, 2, 1 };

			Blob blob(indices.size() * sizeof(unsigned int));
			blob.copyDataFrom(indices.data());

			m_pIndexBuffer = new IndexBuffer;
			m_pIndexBuffer->init(&blob);
		}

		{
			AssetLoader assetLoader;
			Blob* vsBlob = assetLoader.load("assets/shaders/TextureMapScene.vert", AssetType::Shader);
			Blob* psBlob = assetLoader.load("assets/shaders/TextureMapScene.frag", AssetType::Shader);

			m_pShader = new Shader;
			m_pShader->init(vsBlob, psBlob);

			SAFE_DELETE_SET_NULL(vsBlob);
			SAFE_DELETE_SET_NULL(psBlob);
		}

		{
			AssetLoader assetLoader;
			TextureBlob* texBlob = (TextureBlob*)assetLoader.load("assets/textures/skybox.jpeg", AssetType::Texture);

			m_pTexture = new Texture2D;
			m_pTexture->init(texBlob);

			SAFE_DELETE_SET_NULL(texBlob);
		}


		m_bIsInit = true;
	}

	void TextureMapScene::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pVertexArray);
		SAFE_DELETE_SET_NULL(m_pIndexBuffer);
		SAFE_DELETE_SET_NULL(m_pShader);
	}

	void TextureMapScene::Tick(float deltaTime)
	{
		if (m_pShader)
		{
			m_pShader->bind();
			Matrix4x4f scaleMatrix;
			Matrix4x4Scale(scaleMatrix, m_scale.x, m_scale.y, m_scale.z);
			Matrix4x4f rotateMatrix;
			Matrix4x4RotateYawPitchRoll(rotateMatrix, m_rotation.x, m_rotation.y, m_rotation.z, false);
			Matrix4x4f translateMatrix;
			Matrix4x4Translate(translateMatrix, m_translation.x, m_translation.y, m_translation.z);

			m_mvp = translateMatrix * rotateMatrix * scaleMatrix;
			m_pShader->setMat4("u_mvp", m_mvp, true);
		}
			
		if (m_pTexture)
			m_pTexture->bind(0);
		if (m_pVertexArray)
			m_pVertexArray->bind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_pIndexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
		}



		if (m_pShader)
			m_pShader->unbind();
		if (m_pTexture)
			m_pTexture->unbind();
		if (m_pVertexArray)
			m_pVertexArray->unbind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->unbind();
		}

	}

	void TextureMapScene::RecompileShader()
	{
		SAFE_DELETE_SET_NULL(m_pShader);

		AssetLoader assetLoader;
		Blob* vsBlob = assetLoader.load("assets/shaders/TextureMapScene.vert", AssetType::Shader);
		Blob* psBlob = assetLoader.load("assets/shaders/TextureMapScene.frag", AssetType::Shader);

		m_pShader = new Shader;
		m_pShader->init(vsBlob, psBlob);

		SAFE_DELETE_SET_NULL(vsBlob);
		SAFE_DELETE_SET_NULL(psBlob);
	}

	void TextureMapScene::RenderGUI()
	{
		ImGui::DragFloat3("transaltion", m_translation, 0.1f);
		ImGui::DragFloat3("rotate(yaw pitch roll)", m_rotation, 1);
		ImGui::DragFloat3("scale", m_scale, 0.1f);
	}
}