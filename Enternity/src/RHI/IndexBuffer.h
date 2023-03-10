/***************************************************************************************
Author: lvke
Date:
Description:
IndexBuffer : default unsigned int type
****************************************************************************************/
#pragma once

namespace Enternity
{
	class Blob;
	class IndexBuffer
	{
	public:
		~IndexBuffer();
	public:
		void init(Blob* blob);
		void bind();
		void unbind();
		inline unsigned int getCount();
	private:
		unsigned int m_renderId;
		unsigned int m_count;
	};

	inline unsigned int IndexBuffer::getCount()
	{
		return m_count;
	}
}