#pragma once
#include "Engine/BlobHolder.h"

namespace Enternity
{
	class TextureBlobHolder : public BlobHolder
	{
		friend class TextureBlobLoader;
	public:
		TextureBlobHolder(BlobLoader* blobLoader, const std::string& path);
		int getLength();
	private:
		int m_width;
		int m_height;
		int m_channels;
		bool m_bSlip;
	};

	inline int TextureBlobHolder::getLength()
	{
		return m_width * m_height * m_channels;
	}
}