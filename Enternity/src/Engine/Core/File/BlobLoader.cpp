#include "BlobLoader.h"
#include "Core/Log/Log.h"
#include "Core/File/Blob.h"
#include "Core/File/stb_image.h"
#include "Core/ThreadPool/ThreadPool.h"
#include <fstream>

namespace Enternity
{
	void BlobLoader::load(Blob*& blob, const std::string& filePath, AssetType assetType, LoadType loadType)
	{
		switch (assetType)
		{
		case AssetType::General:
		{
			if (loadType == LoadType::Sync)
				loadGeneral(blob, filePath);
			else if(loadType == LoadType::Asyn)
				ThreadPool::GetInstance().commitTask(
					[&]() 
					{
						loadGeneral(blob, filePath);
					});
		}
			break;
		case AssetType::Model:
			break;
		case AssetType::Texture:
		{
			if (loadType == LoadType::Sync)
				loadTexture(blob, filePath);
			else if (loadType == LoadType::Asyn)
				ThreadPool::GetInstance().commitTask(
					[&]()
					{
						loadTexture(blob, filePath);
					});
		}
			break;
		default:
			LOG_ERROR("Unsupported Asset Type");
			ENTERNITY_ASSERT(false);
			break;	
		}
	}

	void BlobLoader::loadGeneral(Blob*& blob, const std::string& filePath)
	{
		std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
		ENTERNITY_ASSERT(ifs.is_open());

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		blob = new Blob(size);
		pFilebuf->sgetn((char*)blob->getData(), blob->getLength());

		ifs.close();
	}

	void BlobLoader::loadTexture(Blob*& blob, const std::string& filePath, int desired_channels)
	{
		unsigned char* tmpTexture;
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(1);
		tmpTexture = stbi_load(filePath.c_str(), &width, &height, &channels, desired_channels);

		blob = new Blob(width * height * channels);
		memcpy_s(blob->getData(), blob->getLength(), tmpTexture, blob->getLength());
		blob->m_width = width;
		blob->m_height = height;
		blob->m_channels = channels;

		stbi_image_free(tmpTexture);
	}
}