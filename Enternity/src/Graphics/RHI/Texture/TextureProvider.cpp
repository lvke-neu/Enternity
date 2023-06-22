#include "TextureProvider.h"
#include "Texture.h"
#include "TextureAsset.h"
#include "Common/Macro.h"

namespace Enternity
{
	Texture* TextureProvider::getTexture(const char* fullPath)
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
}