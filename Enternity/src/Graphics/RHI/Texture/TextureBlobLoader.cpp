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
			doLoadTexture2D(blobHolder);
			return;
		}
		else if (textureBlobHolder->getTextureType() == TextureBlobHolder::Texture_2D_HDR)
		{
			doLoadTexture2DHDR(blobHolder);
			return;
		}
		else if (textureBlobHolder->getTextureType() == TextureBlobHolder::Texture_Cube_Map)
		{
			doLoadTextureCubeMap(blobHolder);
			return;
		}
		else
		{
			LOG_ERROR("TextureBlobHolder type==None");
		}

	}

	void TextureBlobLoader::doLoadTexture2D(BlobHolder* blobHolder)
	{
		m_mtx.lock();

		Texture2DBlobHolder* texture2DBlobHolder = dynamic_cast<Texture2DBlobHolder*>(blobHolder);

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
	}

	void TextureBlobLoader::doLoadTexture2DHDR(BlobHolder* blobHolder)
	{
		m_mtx.lock();

		Texture2DHDRBlobHolder* texture2DHDRBlobHolder = dynamic_cast<Texture2DHDRBlobHolder*>(blobHolder);

		float* tmpTexture;

		stbi_set_flip_vertically_on_load(texture2DHDRBlobHolder->m_bSlip);
		tmpTexture = stbi_loadf(texture2DHDRBlobHolder->getPath(), &texture2DHDRBlobHolder->m_width, &texture2DHDRBlobHolder->m_height, &texture2DHDRBlobHolder->m_channels, 0);
		if (!tmpTexture)
		{
			LOG_ERROR("Texture load failed:{0}", texture2DHDRBlobHolder->getPath());
			texture2DHDRBlobHolder->loadFailed__();
			m_mtx.unlock();
			return;
		}

		Blob* blob = new Blob(texture2DHDRBlobHolder->m_width * texture2DHDRBlobHolder->m_height * texture2DHDRBlobHolder->m_channels * 4);

		memcpy_s(blob->getData(), blob->getLength(), tmpTexture, blob->getLength());

		stbi_image_free(tmpTexture);

		texture2DHDRBlobHolder->loadSucceeded__(blob);
		SAFE_DELETE_SET_NULL(blob);

		m_mtx.unlock();
	}

	void TextureBlobLoader::doLoadTextureCubeMap(BlobHolder* blobHolder)
	{
		m_mtx2.lock();

		TextureCubeMapBlobHolder* textureCubeMapBlobHolder = dynamic_cast<TextureCubeMapBlobHolder*>(blobHolder);

		for (int i = 0; i < 6; i++)
		{
			textureCubeMapBlobHolder->m_texture2DBlobHolders[i] = new Texture2DBlobHolder(this, textureCubeMapBlobHolder->m_paths[i].c_str());
			textureCubeMapBlobHolder->m_texture2DBlobHolders[i]->setSlip(false);
			textureCubeMapBlobHolder->m_texture2DBlobHolders[i]->load(0);
			if (!textureCubeMapBlobHolder->m_texture2DBlobHolders[i]->isLoadSucceeded())
			{
				textureCubeMapBlobHolder->loadFailed__();
				m_mtx2.unlock();
				return;
			}
		}

		textureCubeMapBlobHolder->loadSucceeded__();

		m_mtx2.unlock();
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
		else if (strncmp("TEXTURE_2D_HDR?", texPath.c_str(), 15) == 0)
		{
			return new Texture2DHDRBlobHolder(this, texPath.substr(15).c_str());
		}
		else if(strncmp("CUBE_MAP?", texPath.c_str(), 9) == 0)
		{
			return new TextureCubeMapBlobHolder(this, texPath.substr(9).c_str());
		}


		return  nullptr;
	}

}