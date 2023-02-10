#include "BlobLoader.h"
#include "Core/Log/Log.h"
#include "Core/File/Blob.h"
#include "Core/File/stb_image.h"
#include <fstream>

namespace Enternity
{
	Blob* BlobLoader::load(const std::string& filePath, AssetType assetType)
	{
		switch (assetType)
		{
		case AssetType::General:
			return loadGeneral(filePath);
		case AssetType::Model:
			return nullptr;
		case AssetType::Texture:
			return loadTexture(filePath);
		default:
			LOG_ERROR("Unsupported Asset Type");
			ENTERNITY_ASSERT(false);
			return nullptr;
		}
	}

	Blob* BlobLoader::loadGeneral(const std::string& filePath)
	{
		std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
		ENTERNITY_ASSERT(ifs.is_open());

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		Blob* blob = new Blob(size);
		pFilebuf->sgetn((char*)blob->getData(), blob->getLength());

		ifs.close();

		return blob;
	}

	Blob* BlobLoader::loadTexture(const std::string& filePath)
	{
		unsigned char* tmpTexture;
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(1);
		tmpTexture = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

		Blob* blob = new Blob(width * height * channels);
		memcpy_s(blob->getData(), blob->getLength(), tmpTexture, blob->getLength());
		blob->m_width = width;
		blob->m_height = height;
		blob->m_channels = channels;

		stbi_image_free(tmpTexture);

		return blob;
	}
}