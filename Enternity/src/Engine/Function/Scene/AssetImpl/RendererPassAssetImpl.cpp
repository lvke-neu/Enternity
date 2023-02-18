#include "RendererPassAssetImpl.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/EventManager.h"

namespace Enternity
{
	RendererPassAssetImpl::RendererPassAssetImpl()
	{
		EventManager::GetInstance().registry(EventType::Tick, BIND_FUNC(RendererPassAssetImpl::loadImpl));
	}

	RendererPassAssetImpl::~RendererPassAssetImpl()
	{
		EventManager::GetInstance().unRegistry(EventType::Tick, BIND_FUNC(RendererPassAssetImpl::loadImpl));
		unLoad();
	}

	void RendererPassAssetImpl::load(const std::string& vsFilePath, const std::string& psFilePath)
	{
		unLoad();

		m_vsAsset = Asset({ vsFilePath, AssetType::Shader, AssetLoadType::Asyn });
		m_psAsset = Asset({ psFilePath, AssetType::Shader, AssetLoadType::Asyn });

		AssetLoader assetLoader;
		assetLoader.loadAsset(m_vsAsset);
		assetLoader.loadAsset(m_psAsset);
	}

	void RendererPassAssetImpl::unLoad()
	{
		RenderWrapper::Destroy(m_shader);
		m_vsAsset.reset();
		m_psAsset.reset();
	}

	void RendererPassAssetImpl::setRenderState(RenderState state, bool enable)
	{
		m_renderStates[state] = enable;
	}

	bool RendererPassAssetImpl::getRenderState(RenderState state)
	{
		return m_renderStates[state];
	}

	void RendererPassAssetImpl::loadImpl(IEvent* event)
	{
		if (m_vsAsset.getAssetLoadState() == AssetLoadState::success &&
			m_psAsset.getAssetLoadState() == AssetLoadState::success)
		{
			RenderWrapper::Destroy(m_shader);

			m_shader = RenderWrapper::Create<Shader>();
			m_shader->init(m_vsAsset.getBlob()[0], m_psAsset.getBlob()[0]);

			m_vsAsset.reset();
			m_psAsset.reset();
		}
	}
}