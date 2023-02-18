#include "ShaderAssetImpl.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/EventManager.h"

namespace Enternity
{
	ShaderAssetImpl::ShaderAssetImpl()
	{
		EventManager::GetInstance().registry(EventType::Tick, BIND_FUNC(ShaderAssetImpl::loadImpl));
	}

	ShaderAssetImpl::~ShaderAssetImpl()
	{
		EventManager::GetInstance().unRegistry(EventType::Tick, BIND_FUNC(ShaderAssetImpl::loadImpl));
		unLoad();
	}

	void ShaderAssetImpl::load(const std::string& vsFilePath, const std::string& psFilePath)
	{
		unLoad();

		m_vsAsset = Asset({ vsFilePath, AssetType::Shader, AssetLoadType::Asyn });
		m_psAsset = Asset({ psFilePath, AssetType::Shader, AssetLoadType::Asyn });

		AssetLoader assetLoader;
		assetLoader.loadAsset(m_vsAsset);
		assetLoader.loadAsset(m_psAsset);
	}

	void ShaderAssetImpl::unLoad()
	{
		RenderWrapper::Destroy(m_shader);
		m_vsAsset.reset();
		m_psAsset.reset();
	}

	void ShaderAssetImpl::loadImpl(IEvent* event)
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