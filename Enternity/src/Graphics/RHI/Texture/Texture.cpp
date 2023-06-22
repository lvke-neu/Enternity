#include "Texture.h"
#include "TextureAsset.h"
#include "Engine/Log.h"
#include "Common/Macro.h"
#include <glad/glad.h>

namespace Enternity
{
	Texture::Texture(TextureAsset* textureAsset)
	{
		if (textureAsset)
		{
			CHECK_GL_CALL(glGenTextures(1, &m_renderId));
			CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_renderId));

			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			if (textureAsset->m_channels == 3)
			{
				CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, textureAsset->m_width, textureAsset->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureAsset->m_content));
			}
			else if (textureAsset->m_channels == 4)
			{
				CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureAsset->m_width, textureAsset->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureAsset->m_content));
			}

			CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}

	Texture::~Texture()
	{
		CHECK_GL_CALL(glDeleteTextures(1, &m_renderId));
	}

	void Texture::bind(unsigned int slot)
	{
		CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_renderId));
	}

	void Texture::unbind()
	{
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	}
}