#include "QuadObject.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Blob/Blob.h"
#include "Core/Log/Log.h"
#include "RHI/VertexBuffer.h"
#include "RHI/VertexArray.h"
#include "RHI/IndexBuffer.h"
#include "RHI/Shader.h"
#include "RHI/Texture.h"
#include "GUI/GUIRender.h"
#include "Utility/Utility.h"
#include "Vertex.h"
#include "Camera3D.h"
#include "Light.h"
#include <glad/glad.h>

#pragma warning(disable:4312) 

namespace Enternity
{
	QuadObject::QuadObject(unsigned int texBufferId)
	{
		m_texBufferId = texBufferId;

		{
			VertexBuffer tmpVertexBuffer;
			std::vector<VertexPosNormalTexcoord> vertices;
			vertices.resize(4);

			vertices[0].position = Vector3f(-1.0f, 1.0f, 0.0f);
			vertices[0].texcoord = Vector2f(0.0f, 1.0f);

			vertices[1].position = Vector3f(1.0f, 1.0f, 0.0f);
			vertices[1].texcoord = Vector2f(1.0f, 1.0f);

			vertices[2].position = Vector3f(1.0f, -1.0f, 0.0f);
			vertices[2].texcoord = Vector2f(1.0f, 0.0f);

			vertices[3].position = Vector3f(-1.0f, -1.0f, 0.0f);
			vertices[3].texcoord = Vector2f(0.0f, 0.0f);

			Blob blob(vertices.size() * sizeof(VertexPosNormalTexcoord));
			blob.copyDataFrom(vertices.data());

			tmpVertexBuffer.init(&blob);

			m_pVertexArray = new VertexArray;
			m_pVertexArray->init(&tmpVertexBuffer, &VertexPosNormalTexcoord::vertexBufferLayout);
		}

		{
			std::vector<unsigned int> indices
			{
				3,  1,  0,  3,  2,  1
			};

			Blob blob(indices.size() * sizeof(unsigned int));
			blob.copyDataFrom(indices.data());

			m_pIndexBuffer = new IndexBuffer;
			m_pIndexBuffer->init(&blob);
		}

		{
			AssetLoader assetLoader;
			Blob* vsBlob = assetLoader.load("assets/shaders/QuadScene.vert", AssetType::Shader);
			Blob* psBlob = assetLoader.load("assets/shaders/QuadScene.frag", AssetType::Shader);

			m_pShader = new Shader;
			m_pShader->init(vsBlob, psBlob);

			SAFE_DELETE_SET_NULL(vsBlob);
			SAFE_DELETE_SET_NULL(psBlob);
		}

	}

	QuadObject::~QuadObject()
	{
		SAFE_DELETE_SET_NULL(m_pVertexArray);
		SAFE_DELETE_SET_NULL(m_pIndexBuffer);
		SAFE_DELETE_SET_NULL(m_pShader);
	}

	void QuadObject::Draw()
	{
		
		if (m_pShader)
		{
			m_pShader->bind();

			CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + 0));
			CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_texBufferId));
		}
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


}