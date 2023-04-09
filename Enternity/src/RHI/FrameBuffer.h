#pragma once

namespace Enternity
{
	class FrameBuffer
	{
	public:
		~FrameBuffer();
	public:
		void init(int width, int height);
		void bind();
		void unbind();
		void resize(int width, int height);
		inline unsigned int getRenderId()
		{
			return m_renderId;
		}

		inline unsigned int getTextureId()
		{
			return m_textureColorBuffer;
		}
	private:
		unsigned int m_renderId;
		unsigned int m_textureColorBuffer;
		unsigned int m_rbo;
	};
}