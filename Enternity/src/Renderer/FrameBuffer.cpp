#include "FrameBuffer.h"

BEGIN_ENTERNITY

FrameBuffer::FrameBuffer(unsigned int width, unsigned int height):
	m_width(width), m_height(height)
{
	Rebuild(m_width, m_height);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_rendererId);
	glDeleteFramebuffers(1, &m_rendererIdTmp);
	glDeleteTextures(1, &m_texRendererId);
	glDeleteTextures(1, &m_texRendererIdTmp);
	glDeleteRenderbuffers(1, &m_renderBufferId);
}

void FrameBuffer::Bind(unsigned int slot) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
}

void FrameBuffer::UnBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Resolve()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_rendererId);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_rendererIdTmp);
	glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void FrameBuffer::Rebuild(unsigned int width, unsigned int height)
{
	m_width = width;
	m_height = height;
	//glDeleteFramebuffers(1, &m_rendererId);
	//glDeleteTextures(1, &m_texRendererId);
	//glDeleteRenderbuffers(1, &m_renderBufferId);

	//glGenFramebuffers(1, &m_rendererId);
	//glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);

	////texture
	//glGenTextures(1, &m_texRendererId);
	//glBindTexture(GL_TEXTURE_2D, m_texRendererId);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texRendererId, 0);

	////depth stecil
	//glGenRenderbuffers(1, &m_renderBufferId);
	//glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
	//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

	//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);

	//if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	//	LOG_ERROR("Framebuffer is not complete!");

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDeleteFramebuffers(1, &m_rendererId);
	glDeleteFramebuffers(1, &m_rendererIdTmp);
	glDeleteTextures(1, &m_texRendererId);
	glDeleteTextures(1, &m_texRendererIdTmp);
	glDeleteRenderbuffers(1, &m_renderBufferId);

	glGenFramebuffers(1, &m_rendererId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
	// create a multisampled color attachment texture

	glGenTextures(1, &m_texRendererId);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_texRendererId);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, m_width, m_height, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_texRendererId, 0);
	// create a (also multisampled) renderbuffer object for depth and stencil attachments

	glGenRenderbuffers(1, &m_renderBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, m_width, m_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG_ERROR("Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glGenFramebuffers(1, &m_rendererIdTmp);
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererIdTmp);
	glGenTextures(1, &m_texRendererIdTmp);
	glBindTexture(GL_TEXTURE_2D, m_texRendererIdTmp);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texRendererIdTmp, 0);	// we only need a color buffer

}


//framebufferEx
FrameBufferEx::FrameBufferEx(const FrameBufferSpecification& specification)
{
	m_FrameBufferSpecification = specification;

	for (auto formatSpec : m_FrameBufferSpecification.m_FBAS.m_Attachments)
	{
		if (formatSpec.m_TextureFormat == FrameBufferTextureFormat::DEPTH24STENCIL8)
		{
			m_DepthFTS = formatSpec;
		}
		else
			m_ColorFTS.emplace_back(formatSpec);
	}


	Build();
	//FrameBufferSpecification fbs;
	//fbs.m_Height = 100;
	//fbs.m_Width = 100;
	//fbs.m_FBAS = FrameBufferAttachmentSpecification({ {FrameBufferTextureFormat::RGBA8}, {FrameBufferTextureFormat::DEPTH24STENCIL8} });
}

FrameBufferEx::~FrameBufferEx()
{
	glDeleteFramebuffers(1, &m_rendererId);
	glDeleteTextures(GLsizei(m_texRendererIds.size()), m_texRendererIds.data());
	glDeleteRenderbuffers(1, &m_renderBufferId);
}

void FrameBufferEx::Bind(unsigned int slot) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
	//int value = -1;
	//glClearTexImage(m_texRendererIds[1], 0, GL_RED_INTEGER, GL_INT, &value);
}

void FrameBufferEx::UnBind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferEx::Build()
{
	glDeleteFramebuffers(1, &m_rendererId);
	glDeleteTextures(GLsizei(m_texRendererIds.size()), m_texRendererIds.data());
	m_texRendererIds.clear();
	glDeleteRenderbuffers(1, &m_renderBufferId);
	

	glGenFramebuffers(1, &m_rendererId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);

	if (m_ColorFTS.size())
	{
		m_texRendererIds.resize(m_ColorFTS.size());
		for (int i = 0; i < m_ColorFTS.size(); i++)
		{
			//texture
			glGenTextures(1, &m_texRendererIds[i]);
			glBindTexture(GL_TEXTURE_2D, m_texRendererIds[i]);
			CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GetInternalformat(m_ColorFTS[i].m_TextureFormat), m_FrameBufferSpecification.m_Width, m_FrameBufferSpecification.m_Height, 0, GetFormat(m_ColorFTS[i].m_TextureFormat), GL_UNSIGNED_BYTE, nullptr));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_texRendererIds[i], 0);

		}
		
	}

	//depth stecil
	if (m_DepthFTS.m_TextureFormat != FrameBufferTextureFormat::None)
	{
		glGenRenderbuffers(1, &m_renderBufferId);
		glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferId);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_FrameBufferSpecification.m_Width, m_FrameBufferSpecification.m_Height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferId);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG_ERROR("Framebuffer is not complete!");

	GLenum* buffers = new GLenum[m_texRendererIds.size()];
	for (int i = 0; i < m_texRendererIds.size(); i++)
		buffers[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(GLsizei(m_texRendererIds.size()), buffers);
	delete [] buffers;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLint FrameBufferEx::GetInternalformat(FrameBufferTextureFormat format)
{
	switch (format)
	{
	case FrameBufferTextureFormat::RGBA8:
		return GL_RGBA8;
	case FrameBufferTextureFormat::RED_INTEGER:
		return GL_R32I;
	}
	return -1;
}

GLenum FrameBufferEx::GetFormat(FrameBufferTextureFormat format)
{
	switch (format)
	{
	case FrameBufferTextureFormat::RGBA8:
		return GL_RGBA;
	case FrameBufferTextureFormat::RED_INTEGER:
		return GL_RED_INTEGER;
	}
	return -1;
}

void FrameBufferEx::ReSize(unsigned int width, unsigned int height)
{
	m_FrameBufferSpecification.m_Width = width;
	m_FrameBufferSpecification.m_Height = height;
	Build();
}

END_ENTERNITY