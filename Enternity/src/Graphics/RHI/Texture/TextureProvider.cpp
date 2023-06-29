#include "TextureProvider.h"
#include "Texture.h"
#include "TextureAsset.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Engine/Event/EventSystem.h"

namespace Enternity
{
	TextureProvider::TextureProvider()
	{
		Engine::GetInstance().getEventSystem()->registerEvent(EventType::Tick, BIND(TextureProvider::tick));
	}

	TextureProvider::~TextureProvider()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::Tick, BIND(TextureProvider::tick));
	}

	Texture* TextureProvider::getTextureSync(const char* fullPath)
	{
		TextureAsset* textureAsset = new TextureAsset(fullPath);
		textureAsset->load(0);

		Texture* texture = nullptr;
		
		if (textureAsset->getLoadingState() == Asset::loading_state_succeeded)
		{
			texture = new Texture(textureAsset);
		}
		
		SAFE_DELETE_SET_NULL(textureAsset);

		return texture;
	}

	void TextureProvider::getTextureAsyn(const char* fullPath, std::function<void(Texture*)> callback)
	{
		TextureAsset* textureAsset = new TextureAsset(fullPath);
		textureAsset->load();

		m_map.push_back({ textureAsset, callback });
	}

	CubeMapTexture* TextureProvider::getCubeMapTexture(const std::vector<const char*>& fullPaths)
	{
		if (fullPaths.size() != 6)
		{
			return nullptr;
		}
		
		std::vector<TextureAsset*> textureAssets;

		for (int i = 0; i < 6; ++i)
		{
			TextureAsset* textureAsset = new TextureAsset(fullPaths[i]);
			textureAsset->load(0);
			if (textureAsset->getLoadingState() == Asset::loading_state_succeeded)
			{
				textureAssets.push_back(textureAsset);
			}
		}

		CubeMapTexture* cubeMapTexture = new CubeMapTexture(textureAssets);

		for (int i = 0; i < textureAssets.size(); ++i)
		{
			SAFE_DELETE_SET_NULL(textureAssets[i]);
		}

		return cubeMapTexture;
	}

	void TextureProvider::tick(void* data)
	{
		for (auto it = m_map.begin(); it != m_map.end(); )
		{
			if (it->textureAsset->getLoadingState() == Asset::loading_state_succeeded)
			{
				it->callback(new Texture(it->textureAsset));
				SAFE_DELETE_SET_NULL(it->textureAsset);
				it = m_map.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}