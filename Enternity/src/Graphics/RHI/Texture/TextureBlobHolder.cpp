#include "TextureBlobHolder.h"
#include "Texture.h"

namespace Enternity
{
	//#########################################################################################
	TextureBlobHolder::TextureBlobHolder(BlobLoader* blobLoader, const char* path) :
		BlobHolder(blobLoader, path)
	{

	}

	//#########################################################################################
	Texture2DBlobHolder::Texture2DBlobHolder(BlobLoader* blobLoader, const char* path) :
		TextureBlobHolder(blobLoader, path),
		m_width(0),
		m_height(0),
		m_channels(0),
		m_bSlip(true)
	{
		m_textureType = Texture_2D;
	}

	Asset* Texture2DBlobHolder::createAsset()
	{
		return new Texture2D;
	}

	//#########################################################################################
	TextureCubeMapBlobHolder::TextureCubeMapBlobHolder(BlobLoader* blobLoader, const char* path) :
		TextureBlobHolder(blobLoader, path)
	{
		m_textureType = Texture_Cube_Map;
	}

	Asset* TextureCubeMapBlobHolder::createAsset()
	{
		return new TextureCubeMap;
	}
}