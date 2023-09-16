#include "Texture.h"
#include "Engine/Engine.h"
#include "TextureBlobHolder.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "Engine/RenderView.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/FrameBuffer/FrameBuffer.h"
#include <glm/gtc/quaternion.hpp>
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

		if (texture2DBlobHolder->m_channels == 1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture2DBlobHolder->m_width, texture2DBlobHolder->m_height, 0, GL_RED, GL_UNSIGNED_BYTE, texture2DBlobHolder->getBlob()->getData());
		}
		else if (texture2DBlobHolder->m_channels == 3)
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

	void Texture2D::unbind(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Bind(unsigned int renderId, unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, renderId);
	}

	void Texture2D::UnBind(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	//#########################################################################################
	void Texture2DHDR::load(BlobHolder* blobHolder)
	{
		Texture2DHDRBlobHolder* texture2DHDRBlobHolder = dynamic_cast<Texture2DHDRBlobHolder*>(blobHolder);
		if (!texture2DHDRBlobHolder ||
			!texture2DHDRBlobHolder->isLoadSucceeded() ||
			!texture2DHDRBlobHolder->getBlob())
		{
			m_state = loading_state_failed;
			return;
		}

		glGenTextures(1, &m_renderId);
		glBindTexture(GL_TEXTURE_2D, m_renderId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, texture2DHDRBlobHolder->m_width, texture2DHDRBlobHolder->m_height, 0, GL_RGB, GL_FLOAT, texture2DHDRBlobHolder->getBlob()->getData());

		glBindTexture(GL_TEXTURE_2D, 0);
		m_state = Asset::loading_state_succeeded;
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

	void TextureCubeMap::unbind(unsigned int slot)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, slot);
	}

	//#########################################################################################
	void TextureCubeMapHDR::load(BlobHolder* blobHolder)
	{
		TextureCubeMapHDRBlobHolder* textureCubeMapHDRBlobHolder = dynamic_cast<TextureCubeMapHDRBlobHolder*>(blobHolder);
		if (!textureCubeMapHDRBlobHolder ||
			!textureCubeMapHDRBlobHolder->isLoadSucceeded())
		{
			m_state = loading_state_failed;
			return;
		}

		glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
		glm::mat4 captureViews[] =
		{
		   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
		   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
		   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
		   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		};

		int hdrCubemapWidth = 2048;
		int hdrCubemapHeight = 2048;
		Mesh mesh;
		Renderer renderer;
		Texture2DHDR texture2DHDR;
		FrameBufferWithoutColorAttachment frameBuffer(hdrCubemapWidth, hdrCubemapHeight);
		mesh.load((BlobHolder*)textureCubeMapHDRBlobHolder->m_meshBlobHolder);
		renderer.load((BlobHolder*)textureCubeMapHDRBlobHolder->m_rendererBlobHolder);
		texture2DHDR.load((BlobHolder*)textureCubeMapHDRBlobHolder->m_texture2DHDRBlobHolder);

		if (!mesh.isLoadSucceeded() || !renderer.isLoadSucceeded() || !texture2DHDR.isLoadSucceeded())
		{
			m_state = loading_state_failed;
			return;
		}

		frameBuffer.bind();
		glGenTextures(1, &m_renderId);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_renderId);
		for (int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, hdrCubemapWidth, hdrCubemapHeight, 0, GL_RGB, GL_FLOAT, nullptr);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


		renderer.bind();
		renderer.setMat4("u_p", captureProjection);
		texture2DHDR.bind(0);
		glViewport(0, 0, hdrCubemapWidth, hdrCubemapHeight);
		for (int i = 0; i < 6; ++i)
		{
			renderer.setMat4("u_v", captureViews[i]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, m_renderId, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			mesh.draw();
		}
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glViewport(0, 0, Engine::GetInstance().getRenderView()->getWidth(), Engine::GetInstance().getRenderView()->getHeight());
		texture2DHDR.unbind(0);
		renderer.unbind();
		frameBuffer.unbind();

		m_state = Asset::loading_state_succeeded;
	}
}