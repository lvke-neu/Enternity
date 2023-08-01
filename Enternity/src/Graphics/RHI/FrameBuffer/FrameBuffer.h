#pragma once
#include "FrameBufferDefine.h"
#include <vector>

namespace Enternity
{
	class FrameBuffer
	{
	public:
		FrameBuffer(unsigned int width, unsigned int height, const std::vector<ColorAttachmentFormat>& colorFormat);
		~FrameBuffer();
	public:
		void resize(unsigned int width, unsigned int height);
		unsigned int getTextureId(unsigned int index);
		void readPixelInt(unsigned int index, int x, int y , int* data);

		void bind();
		void unbind();
	private:
		unsigned int getInternalformat(ColorAttachmentFormat colorFormat);
		unsigned int getFormat(ColorAttachmentFormat colorFormat);
	private:
		unsigned int m_renderId;
		std::vector<unsigned int> m_textureIds;
		unsigned int m_depthStecilId;

		std::vector<ColorAttachmentFormat> m_colorFormat;
	};

	inline unsigned int FrameBuffer::getTextureId(unsigned int index)
	{
		return m_textureIds[index];
	}

	class FrameBufferWithoutColorAttachment
	{
	public:
		FrameBufferWithoutColorAttachment(unsigned int width, unsigned int height);
		~FrameBufferWithoutColorAttachment();
	public:
		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
		unsigned int m_depthStecilId;
	};

	class FrameBufferShadowMap
	{
	public:
		FrameBufferShadowMap(unsigned int width, unsigned int height);
		~FrameBufferShadowMap();
	public:
		void bind();
		void unbind();
		unsigned int getTextureId();
	private:
		unsigned int m_renderId;
		unsigned int m_textureId;
	};

	inline unsigned int FrameBufferShadowMap::getTextureId()
	{
		return m_textureId;
	}
}