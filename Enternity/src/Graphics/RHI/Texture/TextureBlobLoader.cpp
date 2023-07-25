#include "TextureBlobLoader.h"
#include "stb_image.h"
#include "Common/Macro.h"
#include "Engine/Blob.h"
#include "Engine/BlobHolder.h"
#include "Engine/Log.h"
#include "TextureBlobHolder.h"

namespace Enternity
{
	TextureBlobLoader::TextureBlobLoader() : BlobLoader("texture://")
	{

	}

	void TextureBlobLoader::doLoad(BlobHolder* blobHolder)
	{
		TextureBlobHolder* textureBlobHolder = dynamic_cast<TextureBlobHolder*>(blobHolder);
		if (!textureBlobHolder || blobHolder->getLoadingState() != BlobHolder::loading_state_pending)
			return;

		if (textureBlobHolder->getTextureType() == TextureBlobHolder::Texture_2D)
		{
			m_mtx.lock();

			Texture2DBlobHolder* texture2DBlobHolder = dynamic_cast<Texture2DBlobHolder*>(textureBlobHolder);

			unsigned char* tmpTexture;

			stbi_set_flip_vertically_on_load(texture2DBlobHolder->m_bSlip);
			tmpTexture = stbi_load(texture2DBlobHolder->getPath(), &texture2DBlobHolder->m_width, &texture2DBlobHolder->m_height, &texture2DBlobHolder->m_channels, 0);
			if (!tmpTexture)
			{
				LOG_ERROR("Texture load failed:{0}", texture2DBlobHolder->getPath());
				texture2DBlobHolder->loadFailed__();
				m_mtx.unlock();
				return;
			}

			Blob* blob = new Blob(texture2DBlobHolder->m_width * texture2DBlobHolder->m_height * texture2DBlobHolder->m_channels);

			memcpy_s(blob->getData(), blob->getLength(), tmpTexture, blob->getLength());

			stbi_image_free(tmpTexture);

			texture2DBlobHolder->loadSucceeded__(blob);
			SAFE_DELETE_SET_NULL(blob);

			m_mtx.unlock();

			return;
		}
		else if (textureBlobHolder->getTextureType() == TextureBlobHolder::Texture_Cube_Map)
		{
			return;
		}
		else
		{
			LOG_ERROR("TextureBlobHolder type==None");
		}

	}

	BlobHolder* TextureBlobLoader::createBlobHolder(const char* path)
	{
		std::string texPath(path);
		size_t pos = texPath.find("://");
		if (pos != texPath.npos)
		{
			texPath = texPath.substr(pos + 3);
		}

		if (strncmp("TEXTURE_2D?", texPath.c_str(), 11) == 0)
		{
			return new Texture2DBlobHolder(this, texPath.substr(11).c_str());
		}
		else if(strncmp("CUBE_MAP?", texPath.c_str(), 9) == 0)
		{
			return new TextureCubeMapBlobHolder(this, texPath.substr(9).c_str());
		}

		return  nullptr;
	}

}