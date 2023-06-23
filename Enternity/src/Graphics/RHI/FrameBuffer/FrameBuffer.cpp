#include "FrameBuffer.h"
#include "Engine/Log.h"
#include "Engine/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
	{
		resize(width, height);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_renderId);
		glDeleteTextures(1, &m_textureId);
		glDeleteRenderbuffers(1, &m_depthStecilId);
	}

	void FrameBuffer::resize(unsigned int width, unsigned int height)
	{
		glDeleteFramebuffers(1, &m_renderId);
		glDeleteTextures(1, &m_textureId);
		glDeleteRenderbuffers(1, &m_depthStecilId);

		glGenFramebuffers(1, &m_renderId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderId);

		//texture
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureId, 0);

		//depth stecil
		glGenRenderbuffers(1, &m_depthStecilId);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthStecilId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStecilId);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_ERROR("Framebuffer is not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderId);
	}

	void FrameBuffer::unbind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}