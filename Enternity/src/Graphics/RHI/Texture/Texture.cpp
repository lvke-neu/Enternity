#include "Texture.h"
#include "TextureBlobHolder.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include <glad/glad.h>

namespace Enternity
{
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_renderId);
	}

	void Texture2D::load(BlobHolder* blobHolder)
	{
		TextureBlobHolder* textureBlobHolder = dynamic_cast<TextureBlobHolder*>(blobHolder);
		if (!textureBlobHolder || 
			!textureBlobHolder->isLoadSucceeded() ||
			!textureBlobHolder->getBlob())
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

		if (textureBlobHolder->m_channels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureBlobHolder->m_width, textureBlobHolder->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBlobHolder->getBlob()->getData());
		}
		else if (textureBlobHolder->m_channels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureBlobHolder->m_width, textureBlobHolder->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureBlobHolder->getBlob()->getData());
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		m_state = Asset::loading_state_succeeded;
	}

	void Texture2D::unload()
	{
		glDeleteTextures(1, &m_renderId);
	}

	void Texture2D::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_renderId);
	}

	void Texture2D::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}