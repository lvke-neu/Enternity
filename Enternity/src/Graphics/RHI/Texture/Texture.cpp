#include "Texture.h"
#include "TextureAsset.h"
#include "Engine/Log.h"
#include "Engine/Blob.h"
#include "Common/Macro.h"
#include <glad/glad.h>

namespace Enternity
{
	Texture::Texture(TextureAsset* textureAsset)
	{
		if (textureAsset && textureAsset->m_content)
		{
			CHECK_GL_CALL(glGenTextures(1, &m_renderId));
			CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_renderId));

			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

			if (textureAsset->m_channels == 3)
			{
				CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureAsset->m_width, textureAsset->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureAsset->m_content->getData()));
			}
			else if (textureAsset->m_channels == 4)
			{
				CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureAsset->m_width, textureAsset->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureAsset->m_content->getData()));
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

	CubeMapTexture::CubeMapTexture(const std::vector<TextureAsset*>& textureAssets)
	{
		if (textureAssets.size() == 6)
		{
			CHECK_GL_CALL(glGenTextures(1, &m_renderId));
			CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderId));

			for (int i = 0; i < textureAssets.size(); ++i)
			{
				if (textureAssets[i] && textureAssets[i]->m_content)
				{
					CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, textureAssets[i]->m_width, textureAssets[i]->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureAssets[i]->m_content->getData()));
					m_fullPaths.push_back(textureAssets[i]->m_fullPath);
				}
			}

			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
			CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		}
	}

	CubeMapTexture::~CubeMapTexture()
	{
		glDeleteTextures(1, &m_renderId);
	}

	void CubeMapTexture::bind(unsigned int slot)
	{
		CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderId));
	}

	void CubeMapTexture::unbind()
	{
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}

}