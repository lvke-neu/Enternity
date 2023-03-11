#include "AssetLoader.h"
#include "Core/Blob/Blob.h"
#include "Core/Log/Log.h"
#include <fstream>
#include "stb_image.h"

namespace Enternity
{

	Blob* AssetLoader::load(const char* assetPath, AssetType type)
	{
		if (type == AssetType::Shader)
			return loadShaderImpl(assetPath);
		else if(type == AssetType::Texture)
			return loadTextureImpl(assetPath);

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

	Blob* AssetLoader::loadTextureImpl(const char* assetPath)
	{
		unsigned char* tmpTexture;
		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(1);
		tmpTexture = stbi_load(assetPath, &width, &height, &channels, 0);
		if (!tmpTexture)
		{
			LOG_ERROR("Assets load failed:{0}", assetPath);
			return nullptr;
		}
		
		TextureBlob* texBlob = new TextureBlob(width * height * channels);
		memcpy_s(texBlob->getData(), texBlob->getLength(), tmpTexture, texBlob->getLength());
		texBlob->m_width = width;
		texBlob->m_height = height;
		texBlob->m_channels = channels;

		stbi_image_free(tmpTexture);

		return texBlob;
	}
}