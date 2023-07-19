#include "TextureBlobHolder.h"

namespace Enternity
{

	TextureBlobHolder::TextureBlobHolder(BlobLoader* blobLoader, const std::string& path) : 
		BlobHolder(blobLoader, path),
		m_width(0),
		m_height(0),
		m_channels(0),
		m_bSlip(true)
	{

	}

}