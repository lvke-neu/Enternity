#include "TextureBlobHolder.h"
#include "Texture.h"

namespace Enternity
{
	TextureBlobHolder::TextureBlobHolder(BlobLoader* blobLoader, const char* path) :
		BlobHolder(blobLoader, path),
		m_width(0),
		m_height(0),
		m_channels(0),
		m_bSlip(true)
	{

	}

	Asset* TextureBlobHolder::createAsset()
	{
		return new Texture2D;
	}
}