#pragma once
#include "Engine/BlobHolder.h"

namespace Enternity
{
	class TextureBlobHolder : public BlobHolder
	{
	public:
		TextureBlobHolder(BlobLoader* blobLoader, const std::string& path);
		int* getWidth();
		int* getHeight();
		int* getChannels();
		bool* getSlip();
		void setSlip(bool b);
		int getLength();
	private:
		int m_width;
		int m_height;
		int m_channels;
		bool m_bSlip;
	};

	inline int* TextureBlobHolder::getWidth()
	{
		return &m_width;
	}

	inline int* TextureBlobHolder::getHeight()
	{
		return &m_height;
	}

	inline int* TextureBlobHolder::getChannels()
	{
		return &m_channels;
	}

	inline bool* TextureBlobHolder::getSlip()
	{
		return&m_bSlip;
	}

	inline void TextureBlobHolder::setSlip(bool b)
	{
		m_bSlip = b;
	}

	inline int TextureBlobHolder::getLength()
	{
		return m_width * m_height * m_channels;
	}
}