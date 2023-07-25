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

		size_t pos = m_path.rfind('/');
		if (pos != std::string::npos)
		{
			std::string prefix = m_path.substr(0, pos);
			std::string suffix = m_path.substr(pos + 1);
			m_paths[0] = prefix + "/right" + suffix;
			m_paths[1] = prefix + "/left" + suffix;
			m_paths[2] = prefix + "/top" + suffix;
			m_paths[3] = prefix + "/bottom" + suffix;
			m_paths[4] = prefix + "/front" + suffix;
			m_paths[5] = prefix + "/back" + suffix;
		}
	}

	Asset* TextureCubeMapBlobHolder::createAsset()
	{
		return new TextureCubeMap;
	}

	void TextureCubeMapBlobHolder::loadSucceeded__()
	{
		m_state = loading_state_succeeded;
	}
}