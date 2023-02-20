#include "RenderPassAssetImpl.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/EventManager.h"

namespace Enternity
{
	RenderPassAssetImpl::RenderPassAssetImpl()
	{
		EventManager::GetInstance().registry(EventType::Tick, BIND_FUNC(RenderPassAssetImpl::loadImpl));
		m_renderStates[RenderState::WireFrame] = false;
		m_renderStates[RenderState::Depth] = true;
	}

	RenderPassAssetImpl::~RenderPassAssetImpl()
	{
		EventManager::GetInstance().unRegistry(EventType::Tick, BIND_FUNC(RenderPassAssetImpl::loadImpl));
		unLoad();
	}

	void RenderPassAssetImpl::load(const std::string& vsFilePath, const std::string& psFilePath)
	{
		unLoad();

		m_vsAsset = Asset({ vsFilePath, AssetType::Shader, AssetLoadType::Asyn });
		m_psAsset = Asset({ psFilePath, AssetType::Shader, AssetLoadType::Asyn });
		m_vsAsset.load();
		m_psAsset.load();
	}

	void RenderPassAssetImpl::unLoad()
	{
		RenderWrapper::Destroy(m_shader);
		m_vsAsset.reset();
		m_psAsset.reset();
	}

	void RenderPassAssetImpl::setRenderState(RenderState state, bool enable)
	{
		m_renderStates[state] = enable;
	}

	bool RenderPassAssetImpl::getRenderState(RenderState state)
	{
		return m_renderStates[state];
	}

	void RenderPassAssetImpl::loadImpl(IEvent* event)
	{
		if (m_vsAsset.getAssetLoadState() == AssetLoadState::Success &&
			m_psAsset.getAssetLoadState() == AssetLoadState::Success)
		{
			RenderWrapper::Destroy(m_shader);

			m_shader = RenderWrapper::Create<Shader>();
			m_shader->init(m_vsAsset.getBlob(), m_psAsset.getBlob());

			m_vsAsset.reset();
			m_psAsset.reset();
		}
	}
}