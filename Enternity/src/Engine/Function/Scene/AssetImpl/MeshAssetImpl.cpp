#include "MeshAssetImpl.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/EventManager.h"
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
		RenderWrapper::Destroy(m_vertexArray);
		RenderWrapper::Destroy(m_vertexbuffer);
		RenderWrapper::Destroy(m_indexbuffer);

		m_meshAsset.reset();
	}

	void MeshAssetImpl::loadImpl(IEvent* event)
	{
		if (m_meshAsset.getAssetLoadState() == AssetLoadState::success)
		{
			RenderWrapper::Destroy(m_vertexArray);
			RenderWrapper::Destroy(m_vertexbuffer);
			RenderWrapper::Destroy(m_indexbuffer);

			m_vertexArray = RenderWrapper::Create<VertexArray>();
			m_vertexbuffer = RenderWrapper::Create<VertexBuffer>();
			m_indexbuffer = RenderWrapper::Create<IndexBuffer>();

			VertexBufferLayout  vertexBufferLayout;
			vertexBufferLayout.push({ 0, 3, GL_FLOAT, false,  8 * sizeof(float), 0 });
			vertexBufferLayout.push({ 1, 3, GL_FLOAT, false,  8 * sizeof(float), 3 * sizeof(float) });
			vertexBufferLayout.push({ 2, 2, GL_FLOAT, false,  8 * sizeof(float), 6 * sizeof(float) });
			m_vertexbuffer->init(m_meshAsset.getBlob()[0], vertexBufferLayout);
			m_indexbuffer->init(m_meshAsset.getBlob()[1]);
			m_vertexArray->init(m_vertexbuffer);

			m_meshAsset.reset();
		}
	}
}