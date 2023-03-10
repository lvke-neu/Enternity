#include "AssetLoader.h"
#include "Core/Blob/Blob.h"
#include "Core/Log/Log.h"
#include <fstream>

namespace Enternity
{

	Blob* AssetLoader::load(const char* assetPath, AssetType type)
	{
		if (type == AssetType::Shader)
			return loadShaderImpl(assetPath);

		return nullptr;
	}

	Blob* AssetLoader::loadShaderImpl(const char* assetPath)
	{
		std::ifstream ifs(assetPath, std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			LOG_ERROR("File {0} can not open", assetPath);
			return nullptr;
		}

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		Blob* blob = new Blob(size);
		pFilebuf->sgetn((char*)blob->getData(), blob->getLength());

		ifs.close();

		return blob;
	}
}