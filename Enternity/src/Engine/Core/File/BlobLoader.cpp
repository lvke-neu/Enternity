#include "BlobLoader.h"
#include "Core/Log/Log.h"
#include "Core/File/Blob.h"
#include "Core/File/stb_image.h"
#include "Core/ThreadPool/ThreadPool.h"
#include <fstream>

namespace Enternity
{
	static int s_desired_channels = 0;

	void BlobLoader::loadGeneral(Blob*& blob, const std::string& filePath, LoadType loadType)
	{
		if (loadType == LoadType::Sync)
			loadGeneralImpl(blob, filePath);
		else if (loadType == LoadType::Asyn)
			ThreadPool::GetInstance().commitTask(
				[&]()
				{
					loadGeneralImpl(blob, filePath);
				});
		else
			blob = nullptr;
	}

	void BlobLoader::loadTexture(Blob*& blob, const std::string& filePath, LoadType loadType, int desired_channels /*= 0*/)
	{
		s_desired_channels = desired_channels;
		if (loadType == LoadType::Sync)
			loadTextureImpl(blob, filePath);
		else if (loadType == LoadType::Asyn)
			ThreadPool::GetInstance().commitTask(
				[&]()
				{
					loadTextureImpl(blob, filePath);
				});
		else
			blob = nullptr;
	}

	void BlobLoader::loadMesh(Blob*& verticesBlob, Blob*& indicesBlob, const std::string& filePath, LoadType loadType)
	{
		if (loadType == LoadType::Sync)
			loadMeshImpl(verticesBlob, indicesBlob, filePath);
		else if (loadType == LoadType::Asyn)
			ThreadPool::GetInstance().commitTask(
				[&]()
				{
					loadMeshImpl(verticesBlob, indicesBlob, filePath);
				});
		else
		{
			verticesBlob = nullptr;
			indicesBlob = nullptr;
		}
	}

	void BlobLoader::loadGeneralImpl(Blob*& blob, const std::string& filePath)
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

	void BlobLoader::loadTextureImpl(Blob*& blob, const std::string& filePath)
	{
		unsigned char* tmpTexture;
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(1);
		tmpTexture = stbi_load(filePath.c_str(), &width, &height, &channels, s_desired_channels);

		blob = new Blob(width * height * channels);
		memcpy_s(blob->getData(), blob->getLength(), tmpTexture, blob->getLength());
		blob->m_width = width;
		blob->m_height = height;
		blob->m_channels = channels;

		stbi_image_free(tmpTexture);
	}

	void BlobLoader::loadMeshImpl(Blob*& verticesBlob, Blob*& indicesBlob, const std::string& filePath)
	{

	}
}