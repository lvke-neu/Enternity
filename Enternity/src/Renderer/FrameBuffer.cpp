#include "FrameBuffer.h"

BEGIN_ENTERNITY

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height)
{
	Rebuild(width, height);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_rendererId);
}

void FrameBuffer::Bind(unsigned int slot) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
}

void FrameBuffer::UnBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Rebuild(unsigned int width, unsigned int height)
{
	glDeleteFramebuffers(1, &m_rendererId);

	glGenFramebuffers(1, &m_rendererId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);

	//texture
	glGenTextures(1, &m_texRendererId);
	glBindTexture(GL_TEXTURE_2D, m_texRendererId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texRendererId, 0);

	//depth stecil
	glGenRenderbuffers(1, &m_renderBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG_ERROR("Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

END_ENTERNITY