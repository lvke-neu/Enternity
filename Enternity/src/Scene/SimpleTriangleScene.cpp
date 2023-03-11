#include "SimpleTriangleScene.h"
#include "Core/Reflection/Reflection.h"
#include "Core/Blob/Blob.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Log/Log.h"
#include "Common/Vertex.h"
#include "RHI/VertexBuffer.h"
#include "RHI/VertexArray.h"
#include "RHI/IndexBuffer.h"
#include "RHI/Shader.h"
#include "Utility/Utility.h"
#include <glad/glad.h>

namespace Enternity
{
	REGISTER_CLASS(IScene, "SimpleTriangleScene", SimpleTriangleScene);

	void SimpleTriangleScene::Initialize()  
	{
		if (m_bIsInit)
			return;

		{
			VertexBuffer tmpVertexBuffer;
			std::vector<VertexPosColor> vertices;
			vertices.resize(3);

			vertices[0].position = Vector3f(-0.5f, 0.0f, 0.0f);
			vertices[1].position = Vector3f(0.0f, 0.5f, 0.0f);
			vertices[2].position = Vector3f(0.5f, 0.0f, 0.0f);
			vertices[0].color = Vector3f(1.0f, 0.0f, 0.0f);
			vertices[1].color = Vector3f(0.0f, 1.0f, 0.0f);
			vertices[2].color = Vector3f(0.0f, 0.0f, 1.0f);

			Blob blob(vertices.size() * sizeof(VertexPosColor));
			blob.copyDataFrom(vertices.data());

			tmpVertexBuffer.init(&blob);

			m_pVertexArray = new VertexArray;
			m_pVertexArray->init(&tmpVertexBuffer, &VertexPosColor::vertexBufferLayout);
		}
		
		{
			std::vector<unsigned int> indices{ 0, 1, 2 };

			Blob blob(indices.size() * sizeof(unsigned int));
			blob.copyDataFrom(indices.data());

			m_pIndexBuffer = new IndexBuffer;
			m_pIndexBuffer->init(&blob);
		}

		{
			AssetLoader assetLoader;
			Blob* vsBlob = assetLoader.load("assets/shaders/SimpleTriangleScene.vert", AssetType::Shader);
			Blob* psBlob = assetLoader.load("assets/shaders/SimpleTriangleScene.frag", AssetType::Shader);

			m_pShader = new Shader;
			m_pShader->init(vsBlob, psBlob);

			SAFE_DELETE_SET_NULL(vsBlob);
			SAFE_DELETE_SET_NULL(psBlob);
		}

		m_bIsInit = true;
	}

	void SimpleTriangleScene::Finalize()  
	{
		SAFE_DELETE_SET_NULL(m_pVertexArray);
		SAFE_DELETE_SET_NULL(m_pIndexBuffer);
		SAFE_DELETE_SET_NULL(m_pShader);
	}

	void SimpleTriangleScene::Tick(float deltaTime)  
	{
		if (m_pShader)
			m_pShader->bind();
		if (m_pVertexArray)
			m_pVertexArray->bind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_pIndexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
		}

		if (m_pShader)
			m_pShader->unbind();
		if (m_pVertexArray)
			m_pVertexArray->unbind();
		if (m_pIndexBuffer)
		{
			m_pIndexBuffer->unbind();
		}
	}

	void SimpleTriangleScene::RecompileShader()
	{
		SAFE_DELETE_SET_NULL(m_pShader);

		AssetLoader assetLoader;
		Blob* vsBlob = assetLoader.load("assets/shaders/SimpleTriangleScene.vert", AssetType::Shader);
		Blob* psBlob = assetLoader.load("assets/shaders/SimpleTriangleScene.frag", AssetType::Shader);

		m_pShader = new Shader;
		m_pShader->init(vsBlob, psBlob);

		SAFE_DELETE_SET_NULL(vsBlob);
		SAFE_DELETE_SET_NULL(psBlob);
	}
}