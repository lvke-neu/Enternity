#pragma once
#include "Engine/BlobHolder.h"

namespace Enternity
{
	class TextureBlobHolder : public BlobHolder
	{
		friend class Texture2D;
		friend class TextureBlobLoader;
	public:
		TextureBlobHolder(BlobLoader* blobLoader, const char* path);
		virtual Asset* createAsset() override;
	public:
		int getWidth();
		int getHeight();
		int getChannels();
		void setSlip(bool flag);
	private:
		int m_width;
		int m_height;
		int m_channels;
		bool m_bSlip;
	};

	inline void TextureBlobHolder::setSlip(bool flag)
	{
		m_bSlip = flag;
	}

	inline int TextureBlobHolder::getWidth()
	{
		return m_width;
	}

	inline int TextureBlobHolder::getHeight()
	{
		return m_height;
	}

	inline int TextureBlobHolder::getChannels()
	{
		return m_channels;
	}
}