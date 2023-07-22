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
		if (blobHolder->getLoadingState() != BlobHolder::loading_state_pending)
			return;

		TextureBlobHolder* textureBlobHolder = dynamic_cast<TextureBlobHolder*>(blobHolder);
		if (!textureBlobHolder)
			return;

		m_mtx.lock();

		unsigned char* tmpTexture;

		stbi_set_flip_vertically_on_load(textureBlobHolder->m_bSlip);
		tmpTexture = stbi_load(textureBlobHolder->getPath(), &textureBlobHolder->m_width, &textureBlobHolder->m_height, &textureBlobHolder->m_channels, 0);
		if (!tmpTexture)
		{
			LOG_ERROR("Texture load failed:{0}", textureBlobHolder->getPath());
			textureBlobHolder->loadFailed__();
			m_mtx.unlock();
			return;
		}

		Blob* blob = new Blob(textureBlobHolder->m_width * textureBlobHolder->m_height * textureBlobHolder->m_channels);

		memcpy_s(blob->getData(), blob->getLength(), tmpTexture, blob->getLength());

		stbi_image_free(tmpTexture);

		textureBlobHolder->loadSucceeded__(blob);
		SAFE_DELETE_SET_NULL(blob);

		m_mtx.unlock();
	}

	BlobHolder* TextureBlobLoader::createBlobHolder(const char* path)
	{
		return new TextureBlobHolder(this, path);
	}

}