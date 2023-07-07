#pragma once

namespace Enternity
{
	class FrameBuffer
	{
	public:
		FrameBuffer(unsigned int width, unsigned int height);
		~FrameBuffer();
	public:
		void resize(unsigned int width, unsigned int height);
		unsigned int getTextureId();

		void bind();
		void unbind();
	private:
		unsigned int m_renderId;
		unsigned int m_textureId = -1;
		unsigned int m_depthStecilId;
	};

	inline unsigned int FrameBuffer::getTextureId()
	{
		return m_textureId;
	}
}