#include "FrameBuffer.h"
#include "Core/Log/Log.h"
#include "Utility/Utility.h"
#include <glad/glad.h>

namespace Enternity
{

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_renderId);
	}

	void FrameBuffer::init(int width, int height)
	{
		resize(width, height);
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderId);
	}

	void FrameBuffer::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::resize(int width, int height)
	{
		CHECK_GL_CALL(glDeleteTextures(1, &m_textureColorBuffer));
		CHECK_GL_CALL(glDeleteRenderbuffers(1, &m_rbo));
		CHECK_GL_CALL(glDeleteFramebuffers(1, &m_renderId););

		CHECK_GL_CALL(glGenFramebuffers(1, &m_renderId));
		CHECK_GL_CALL(glBindFramebuffer(GL_FRAMEBUFFER, m_renderId));

		CHECK_GL_CALL(glGenTextures(1, &m_textureColorBuffer));
		CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer));
		CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		CHECK_GL_CALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0));

		CHECK_GL_CALL(glGenRenderbuffers(1, &m_rbo));
		CHECK_GL_CALL(glBindRenderbuffer(GL_RENDERBUFFER, m_rbo));
		CHECK_GL_CALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
		CHECK_GL_CALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo));

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_ERROR("GL_FRAMEBUFFER_NOT_COMPLETE");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}