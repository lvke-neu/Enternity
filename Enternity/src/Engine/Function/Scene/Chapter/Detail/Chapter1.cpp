#include "Chapter1.h"
#include "Function/Scene/Chapter/Common/InputLayout.h"
#include "Core/Memory/Blob.h"
#include "Core/Asset/Asset.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Log/Log.h"


namespace Enternity
{
	Chapter1::Chapter1()
	{
		{
			std::vector<VertexPosColor> vertices;
			vertices.resize(3);

			vertices[0].position = Vector3f(-0.5f, 0.0f, 0.0f);
			vertices[1].position = Vector3f(0.0f, 0.5f,  0.0f);
			vertices[2].position = Vector3f(0.5f, 0.0f,  0.0f);
			vertices[0].color = Vector3f(1.0f, 0.0f, 0.0f);
			vertices[1].color = Vector3f(0.0f, 1.0f, 0.0f);
			vertices[2].color = Vector3f(0.0f, 0.0f, 1.0f);

			Blob blob(vertices.size() * sizeof(VertexPosColor));
			blob.copyDataFrom(vertices.data());

			m_vertexBuffer->init(&blob, InputLayout::VertexBufferLayout_POS_COLOR);
		}

		{
			std::vector<unsigned int> indices{0, 1, 2};

			Blob blob(indices.size() * sizeof(unsigned int));
			blob.copyDataFrom(indices.data());

			m_indexBuffer->init(&blob);
		}

		{
			m_vertexArray->init(m_vertexBuffer);
		}

		{
			Asset vsAsset({ "assets/shaders/Chapter/Chapter1.vert", AssetType::Shader, AssetLoadType::Sync });
			Asset psAsset({ "assets/shaders/Chapter/Chapter1.frag", AssetType::Shader, AssetLoadType::Sync });
			AssetLoader assetLoader;
			assetLoader.loadAsset(vsAsset);
			assetLoader.loadAsset(psAsset);

			m_shader->init(vsAsset.getBlob(), psAsset.getBlob());
		}

	}

	Chapter1::~Chapter1()
	{

	}

	void Chapter1::tick(float deltaTime)
	{
		CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)));

		m_shader->bind();
		m_vertexArray->bind();
		m_indexBuffer->bind();
		CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, m_indexBuffer->getCount(), GL_UNSIGNED_INT, (void*)0));
	}
}


