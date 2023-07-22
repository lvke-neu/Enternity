#pragma once
#include "Engine/BlobHolder.h"

namespace Enternity
{
	class TextureBlobHolder : public BlobHolder
	{
		friend class Texture2D;
		friend class TextureBlobLoader;
	public:
		TextureBlobHolder(BlobLoader* blobLoader, const std::string& path);
		virtual Asset* createAsset() override;
	private:
		int m_width;
		int m_height;
		int m_channels;
		bool m_bSlip;
	};
}