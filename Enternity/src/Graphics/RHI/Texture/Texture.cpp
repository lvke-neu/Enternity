#include "Texture.h"
#include "TextureAsset.h"

namespace Enternity
{
	Texture::Texture(TextureAsset* textureAsset)
	{
		if (textureAsset)
		{
			//TODO:remove
			m_width = textureAsset->m_width;
			m_height = textureAsset->m_height;
			m_channels = textureAsset->m_channels;

			//TODO:create GL_TEXTURE

		}
	}

	Texture::~Texture()
	{
		//TODO:destroy GL_TEXTURE
	}
}