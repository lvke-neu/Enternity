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

	CubeMapTexture* TextureProvider::getCubeMapTextureSync(const std::vector<const char*>& fullPaths)
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

	void TextureProvider::getCubeMapTextureAsyn(const std::vector<const char*>& fullPaths, std::function<void(CubeMapTexture*)> callback)
	{
		if (fullPaths.size() != 6)
		{
			callback(nullptr);
		}

		TextureAsset_Callback2  textureAsset_Callback2;
		textureAsset_Callback2.callback = callback;

		for (int i = 0; i < 6; ++i)
		{
			TextureAsset* textureAsset = new TextureAsset(fullPaths[i]);
			textureAsset->load();
			textureAsset_Callback2.textureAssets.push_back(textureAsset);
		}

		m_map2.push_back(textureAsset_Callback2);
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

		for (auto it = m_map2.begin(); it != m_map2.end(); )
		{
			if(	it->textureAssets[0]->getLoadingState() == Asset::loading_state_succeeded &&
				it->textureAssets[1]->getLoadingState() == Asset::loading_state_succeeded &&
				it->textureAssets[2]->getLoadingState() == Asset::loading_state_succeeded &&
				it->textureAssets[3]->getLoadingState() == Asset::loading_state_succeeded &&
				it->textureAssets[4]->getLoadingState() == Asset::loading_state_succeeded &&
				it->textureAssets[5]->getLoadingState() == Asset::loading_state_succeeded)
			{
				it->callback(new CubeMapTexture(it->textureAssets));
				SAFE_DELETE_SET_NULL(it->textureAssets[0]);
				SAFE_DELETE_SET_NULL(it->textureAssets[1]);
				SAFE_DELETE_SET_NULL(it->textureAssets[2]);
				SAFE_DELETE_SET_NULL(it->textureAssets[3]);
				SAFE_DELETE_SET_NULL(it->textureAssets[4]);
				SAFE_DELETE_SET_NULL(it->textureAssets[5]);
				it = m_map2.erase(it);				   
			}
			else
			{
				it++;
			}
		}
	}
}