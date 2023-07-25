#include "Texture.h"
#include "TextureBlobHolder.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include <glad/glad.h>

namespace Enternity
{
	//#########################################################################################
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_renderId);
	}

	void Texture2D::load(BlobHolder* blobHolder)
	{
		Texture2DBlobHolder* texture2DBlobHolder = dynamic_cast<Texture2DBlobHolder*>(blobHolder);
		if (!texture2DBlobHolder ||
			!texture2DBlobHolder->isLoadSucceeded() ||
			!texture2DBlobHolder->getBlob())
		{
			m_state = loading_state_failed;
			return;
		}

		glGenTextures(1, &m_renderId);
		glBindTexture(GL_TEXTURE_2D, m_renderId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (texture2DBlobHolder->m_channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture2DBlobHolder->m_width, texture2DBlobHolder->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture2DBlobHolder->getBlob()->getData());
		}
		else if (texture2DBlobHolder->m_channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture2DBlobHolder->m_width, texture2DBlobHolder->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture2DBlobHolder->getBlob()->getData());
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		m_state = Asset::loading_state_succeeded;
	}

	void Texture2D::unload()
	{
		glDeleteTextures(1, &m_renderId);
		m_state = loading_state_pending;
	}

	void Texture2D::bind(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_renderId);
	}

	void Texture2D::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Bind(unsigned int renderId, unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, renderId);
	}

	void Texture2D::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//#########################################################################################
	TextureCubeMap::~TextureCubeMap()
	{
		glDeleteTextures(1, &m_renderId);
	}

	void TextureCubeMap::load(BlobHolder* blobHolder)
	{
		TextureCubeMapBlobHolder* textureCubeMapBlobHolder = dynamic_cast<TextureCubeMapBlobHolder*>(blobHolder);
		if (!textureCubeMapBlobHolder ||
			!textureCubeMapBlobHolder->isLoadSucceeded())
		{
			m_state = loading_state_failed;
			return;
		}

		glGenTextures(1, &m_renderId);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderId);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		for (int i = 0; i < 6; ++i)
		{
			
			if (!textureCubeMapBlobHolder->m_texture2DBlobHolders[i] || !textureCubeMapBlobHolder->m_texture2DBlobHolders[i]->getBlob())
			{
				m_state = loading_state_failed;
				return;
			}
			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 
				textureCubeMapBlobHolder->m_texture2DBlobHolders[i]->getWidth(), textureCubeMapBlobHolder->m_texture2DBlobHolders[i]->getHeight(),
				0, GL_RGB, GL_UNSIGNED_BYTE, 
				textureCubeMapBlobHolder->m_texture2DBlobHolders[i]->getBlob()->getData());
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		m_state = Asset::loading_state_succeeded;
	}

	void TextureCubeMap::unload()
	{
		glDeleteTextures(1, &m_renderId);
		m_state = loading_state_pending;
	}

	void TextureCubeMap::bind(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderId);
	}

	void TextureCubeMap::unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
}