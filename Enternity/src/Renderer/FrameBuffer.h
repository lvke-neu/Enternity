/***************************************************************************************
Author: lvke
Date:2023/1/8 12:26
Description:
Encapsulate  FrameBuffer
****************************************************************************************/
#pragma once

#include "Interface/BindableInterface.h"

BEGIN_ENTERNITY

class FrameBuffer : public IBindable
{
public:
	FrameBuffer(unsigned int width, unsigned int height);
	virtual ~FrameBuffer();

	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;
	void Resolve();
	void Rebuild(unsigned int width, unsigned int height);
	inline unsigned int GetTextureRendererId() const { return m_texRendererIdTmp; }
private:
	unsigned int m_texRendererId;
	unsigned int m_renderBufferId;

	uint32_t m_width;
	uint32_t m_height;

	unsigned int m_texRendererIdTmp;
	unsigned int m_rendererIdTmp;

};


//framebufferEx
enum class FrameBufferTextureFormat
{
	None = 0,

	//color
	RGBA8,

	//depth/stencil
	DEPTH24STENCIL8
};

struct FrameBufferTextureSpecification
{
	FrameBufferTextureSpecification() = default;
	FrameBufferTextureSpecification(FrameBufferTextureFormat format) :
		m_TextureFormat(format)
	{

	}
	FrameBufferTextureFormat m_TextureFormat = FrameBufferTextureFormat::None;
	//TODO: filtering/wrap
};

struct FrameBufferAttachmentSpecification
{
	FrameBufferAttachmentSpecification() = default;
	FrameBufferAttachmentSpecification(const std::vector<FrameBufferTextureSpecification>& attachments) :
		m_Attachments(attachments)
	{

	}

	std::vector<FrameBufferTextureSpecification> m_Attachments;
};

struct FrameBufferSpecification
{
	unsigned int m_Width;
	unsigned int m_Height;
	FrameBufferAttachmentSpecification m_FBAS;
};

class FrameBufferEx : public IBindable
{
public:
	FrameBufferEx(const FrameBufferSpecification& specification);
	virtual ~FrameBufferEx();

	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;
	void ReSize(unsigned int width, unsigned int height);
	inline unsigned int GetTextureRendererId(unsigned int index) const { return m_texRendererIds[index]; }
private:
	void Build();
	GLint GetType(FrameBufferTextureFormat format);
private:
	FrameBufferSpecification m_FrameBufferSpecification;
	std::vector<unsigned int> m_texRendererIds;
	unsigned int m_renderBufferId;

	std::vector<FrameBufferTextureSpecification> m_ColorFTS;
	FrameBufferTextureSpecification m_DepthFTS;
};

END_ENTERNITY
