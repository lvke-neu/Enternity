#include "FrameBuffer.h"
#include "Engine/Log.h"
#include "Engine/Blob.h"
#include <glad/glad.h>

namespace Enternity
{
	FrameBuffer::FrameBuffer(unsigned int width, unsigned int height, const std::vector<ColorAttachmentFormat>& colorFormat) :
		m_colorFormat(colorFormat)
	{
		resize(width, height);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_renderId);
		glDeleteTextures(GLsizei(m_textureIds.size()), m_textureIds.data());  
		m_textureIds.clear();
		glDeleteRenderbuffers(1, &m_depthStecilId);
	}

	void FrameBuffer::resize(unsigned int width, unsigned int height)
	{
		glDeleteFramebuffers(1, &m_renderId);
		glDeleteTextures(GLsizei(m_textureIds.size()), m_textureIds.data());
		m_textureIds.clear();
		glDeleteRenderbuffers(1, &m_depthStecilId);

		glGenFramebuffers(1, &m_renderId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderId);

		//texture
		m_textureIds.resize(m_colorFormat.size());
		for (int i = 0; i < m_colorFormat.size(); ++i)
		{
			glGenTextures(1, &m_textureIds[i]);
			glBindTexture(GL_TEXTURE_2D, m_textureIds[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, getInternalformat(m_colorFormat[i]), width, height, 0, getFormat(m_colorFormat[i]), GL_UNSIGNED_BYTE, nullptr);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textureIds[i], 0);
		}

		//depth stecil
		glGenRenderbuffers(1, &m_depthStecilId);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthStecilId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStecilId);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_ERROR("Framebuffer is not complete!");

		std::vector<unsigned int> buffers;
		buffers.resize(m_colorFormat.size());
		for (int i = 0; i < m_colorFormat.size(); i++)
		{
			buffers[i]= GL_COLOR_ATTACHMENT0 + i;
		}
		glDrawBuffers(GLsizei(buffers.size()), buffers.data());

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::readPixelInt(unsigned int index, int x, int y, int* data)
	{
		bind();
		glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, data);
		unbind();
	}

	void FrameBuffer::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderId);
	}

	void FrameBuffer::unbind() 
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	unsigned int FrameBuffer::getInternalformat(ColorAttachmentFormat colorFormat)
	{
		switch (colorFormat)
		{
		case ColorAttachmentFormat::RGB8:
			return GL_RGB8;
		case ColorAttachmentFormat::RGBA8:
			return GL_RGBA8;
		case ColorAttachmentFormat::RED_INTEGER:
			return GL_R32I;
		}
		return -1;
	}

	unsigned int FrameBuffer::getFormat(ColorAttachmentFormat colorFormat)
	{
		switch (colorFormat)
		{
		case ColorAttachmentFormat::RGB8:
			return GL_RGB;
		case ColorAttachmentFormat::RGBA8:
			return GL_RGBA;
		case ColorAttachmentFormat::RED_INTEGER:
			return GL_RED_INTEGER;
		}
		return -1;
	}

	FrameBufferWithoutColorAttachment::FrameBufferWithoutColorAttachment(unsigned int width, unsigned int height)
	{
		glDeleteFramebuffers(1, &m_renderId);
		glDeleteRenderbuffers(1, &m_depthStecilId);

		glGenFramebuffers(1, &m_renderId);
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderId);

		//depth stecil
		glGenRenderbuffers(1, &m_depthStecilId);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthStecilId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthStecilId);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_ERROR("Framebuffer is not complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBufferWithoutColorAttachment::~FrameBufferWithoutColorAttachment()
	{

	}

	void FrameBufferWithoutColorAttachment::bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_renderId);
	}

	void FrameBufferWithoutColorAttachment::unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}