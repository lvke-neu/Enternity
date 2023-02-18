#include "Texture.h"
#include "Core/Log/Log.h"
#include "Core/Memory/Blob.h"
#include <glad/glad.h>

namespace Enternity
{	
	//*************************Texture2D*************************
	void Texture2D::Destroy()
	{
		CHECK_GL_CALL(glDeleteTextures(1, &m_renderId));
	}

	void Texture2D::init(Blob* blob)
	{
		ENTERNITY_ASSERT(blob != nullptr);
		CHECK_GL_CALL(glGenTextures(1, &m_renderId));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_renderId));

		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

		if (blob->m_channels == 3)
		{
			CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, blob->m_width, blob->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, blob->getData()));
		}
		else if (blob->m_channels == 4)
		{
			CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, blob->m_width, blob->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, blob->getData()));
		}
				
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void Texture2D::bind(unsigned int slot)
	{
		CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_renderId));
	}

	void Texture2D::unbind()
	{
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
	}
	//***********************************************************


	//*************************TextureCube***********************
	void TextureCube::Destroy()
	{
		glDeleteTextures(1, &m_renderId);
	}

	void TextureCube::init(const std::vector<Blob*>& blobs)
	{
		ENTERNITY_ASSERT(blobs.size() == 6);

		CHECK_GL_CALL(glGenTextures(1, &m_renderId));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderId));

		int index = 0;
		for (const auto& blob : blobs)
		{
			ENTERNITY_ASSERT(blob != nullptr);

			if (blob->m_channels == 3)
			{
				CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGB8, blob->m_width, blob->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, blob->getData()));
			}
			else if (blob->m_channels == 4)
			{
				CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGBA8, blob->m_width, blob->m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, blob->getData()));
			}
			index++;
		}

		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));

		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}

	void TextureCube::bind(unsigned int slot)
	{
		CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderId));
	}

	void TextureCube::unbind()
	{
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}
	//************************************************************
}