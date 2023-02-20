#include "MeshAssetImpl.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/EventManager.h"
#include "Core/Memory/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	MeshAssetImpl::MeshAssetImpl()
	{
		EventManager::GetInstance().registry(EventType::Tick, BIND_FUNC(MeshAssetImpl::loadImpl));
	}

	MeshAssetImpl::~MeshAssetImpl()
	{
		EventManager::GetInstance().unRegistry(EventType::Tick, BIND_FUNC(MeshAssetImpl::loadImpl));
		unLoad();
	}

	void MeshAssetImpl::load(const std::string& mshFilePath)
	{
		unLoad();

		m_meshAsset = Asset({ mshFilePath, AssetType::Mesh, AssetLoadType::Asyn });
		m_meshAsset.load();
	}

	void MeshAssetImpl::unLoad()
	{
		for(auto& vertexArray : m_vertexArraies)
			RenderWrapper::Destroy(vertexArray);

		for (auto& vertexbuffer : m_vertexbuffers)
			RenderWrapper::Destroy(vertexbuffer);

		for (auto& indexbuffer : m_indexbuffers)
			RenderWrapper::Destroy(indexbuffer);

		m_meshAsset.reset();
	}

	std::vector<VertexArray*>& MeshAssetImpl::getVertexArraies()
	{
		return m_vertexArraies;
	}

	std::vector<IndexBuffer*>& MeshAssetImpl::getIndexBuffers()
	{
		return m_indexbuffers;
	}

	void MeshAssetImpl::loadImpl(IEvent* event)
	{
		if (m_meshAsset.getAssetLoadState() == AssetLoadState::Success)
		{
			for (auto& vertexArray : m_vertexArraies)
				RenderWrapper::Destroy(vertexArray);

			for (auto& vertexbuffer : m_vertexbuffers)
				RenderWrapper::Destroy(vertexbuffer);

			for (auto& indexbuffer : m_indexbuffers)
				RenderWrapper::Destroy(indexbuffer);

			
			VertexBufferLayout  vertexBufferLayout;
			vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
			vertexBufferLayout.push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
			vertexBufferLayout.push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
			
			auto& meshs = m_meshAsset.getMeshs();
			for (auto& mesh : meshs)
			{
				m_vertexArraies.emplace_back(RenderWrapper::Create<VertexArray>());
				m_vertexbuffers.emplace_back(RenderWrapper::Create<VertexBuffer>());
				m_indexbuffers.emplace_back(RenderWrapper::Create<IndexBuffer>());
				
				Blob vtxBlob(mesh.vertices.size() * sizeof(VertexPosNorTex));
				vtxBlob.copyDataFrom(mesh.vertices.data());
				Blob idxBlob(mesh.indices.size() * sizeof(unsigned int));
				idxBlob.copyDataFrom(mesh.indices.data());

				m_vertexbuffers.back()->init(&vtxBlob, vertexBufferLayout);
				m_indexbuffers.back()->init(&idxBlob);
				m_vertexArraies.back()->init(m_vertexbuffers.back());
			}

			m_meshAsset.reset();
		}
	}
}