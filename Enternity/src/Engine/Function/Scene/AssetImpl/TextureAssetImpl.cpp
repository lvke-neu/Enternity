#include "TextureAssetImpl.h"
#include "Function/Render/Wrapper/RenderWrapper.h"
#include "Core/Asset/AssetLoader.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/EventManager.h"

namespace Enternity
{
	TextureAssetImpl::TextureAssetImpl()
	{
		EventManager::GetInstance().registry(EventType::Tick, BIND_FUNC(TextureAssetImpl::loadImpl));
	}

	TextureAssetImpl::~TextureAssetImpl()
	{
		EventManager::GetInstance().unRegistry(EventType::Tick, BIND_FUNC(TextureAssetImpl::loadImpl));
		unLoad();
	}

	void TextureAssetImpl::load(const std::string& matFilePath)
	{
		unLoad();

		m_textureAsset = Asset({ matFilePath, AssetType::Texture, AssetLoadType::Asyn });
		
		AssetLoader assetLoader;
		assetLoader.loadAsset(m_textureAsset);
	}

	void TextureAssetImpl::unLoad()
	{
		RenderWrapper::Destroy(m_texture2D);
		m_textureAsset.reset();
	}

	void TextureAssetImpl::loadImpl(IEvent* event)
	{
		if (m_textureAsset.getAssetLoadState() == AssetLoadState::success)
		{
			RenderWrapper::Destroy(m_texture2D);

			m_texture2D = RenderWrapper::Create<Texture2D>();
			m_texture2D->init(m_textureAsset.getBlob()[0]);

			m_textureAsset.reset();
		}
	}
}