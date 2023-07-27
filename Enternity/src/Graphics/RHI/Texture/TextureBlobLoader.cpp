#include "TextureBlobLoader.h"
#include "stb_image.h"
#include "TextureBlobHolder.h"
#include "Common/Macro.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoaderManager.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Graphics/RHI/Renderer/RendererBlobHolder.h"

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
		else if (textureBlobHolder->getTextureType() == TextureBlobHolder::Texture_Cube_Map_HDR)
		{
			doLoadTextureCubeMapHDR(blobHolder);
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

		textureCubeMapBlobHolder->loadSucceeded__(nullptr);

		m_mtx2.unlock();
	}

	void TextureBlobLoader::doLoadTextureCubeMapHDR(BlobHolder* blobHolder)
	{
		m_mtx2.lock();

		TextureCubeMapHDRBlobHolder* textureCubeMapHDRBlobHolder = dynamic_cast<TextureCubeMapHDRBlobHolder*>(blobHolder);
		
		std::string meshPath = "mesh://primitive=cube";
		textureCubeMapHDRBlobHolder->m_meshBlobHolder = dynamic_cast<MeshBlobHolder*>(Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(meshPath.c_str())->createBlobHolder(meshPath.c_str()));

		std::string rendererPath = "renderer://assets/shaders/hdr/hdr.rdr";
		textureCubeMapHDRBlobHolder->m_rendererBlobHolder = dynamic_cast<RendererBlobHolder*>(Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(rendererPath.c_str())->createBlobHolder(rendererPath.c_str()));

		std::string texture2DHDRPath = "texture://TEXTURE_2D_HDR?" + textureCubeMapHDRBlobHolder->m_path;
		textureCubeMapHDRBlobHolder->m_texture2DHDRBlobHolder = dynamic_cast<Texture2DHDRBlobHolder*>(Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(texture2DHDRPath.c_str())->createBlobHolder(texture2DHDRPath.c_str()));

		if (textureCubeMapHDRBlobHolder->m_meshBlobHolder && textureCubeMapHDRBlobHolder->m_rendererBlobHolder && textureCubeMapHDRBlobHolder->m_texture2DHDRBlobHolder)
		{
			textureCubeMapHDRBlobHolder->m_meshBlobHolder->load(0);
			textureCubeMapHDRBlobHolder->m_rendererBlobHolder->load(0);
			textureCubeMapHDRBlobHolder->m_texture2DHDRBlobHolder->load(0);

			if (textureCubeMapHDRBlobHolder->m_meshBlobHolder->isLoadSucceeded() && textureCubeMapHDRBlobHolder->m_rendererBlobHolder->isLoadSucceeded() && textureCubeMapHDRBlobHolder->m_texture2DHDRBlobHolder->isLoadSucceeded())
			{
				textureCubeMapHDRBlobHolder->loadSucceeded__(nullptr);
				m_mtx2.unlock();
				return;
			}

		}
		textureCubeMapHDRBlobHolder->loadFailed__();
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
		else if (strncmp("TEXTURE_2D&Slip=true?", texPath.c_str(), 21) == 0)
		{
			Texture2DBlobHolder* texture2DBlobHolder = new Texture2DBlobHolder(this, texPath.substr(21).c_str());
			texture2DBlobHolder->setSlip(true);
			return texture2DBlobHolder;
		}
		else if (strncmp("TEXTURE_2D_HDR?", texPath.c_str(), 15) == 0)
		{
			return new Texture2DHDRBlobHolder(this, texPath.substr(15).c_str());
		}
		else if(strncmp("CUBE_MAP?", texPath.c_str(), 9) == 0)
		{
			return new TextureCubeMapBlobHolder(this, texPath.substr(9).c_str());
		}
		else if (strncmp("CUBE_MAP_HDR?", texPath.c_str(), 13) == 0)
		{
			return new TextureCubeMapHDRBlobHolder(this, texPath.substr(13).c_str());
		}

		return  nullptr;
	}

}