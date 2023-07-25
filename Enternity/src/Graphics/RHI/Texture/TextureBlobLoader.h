#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class TextureBlobLoader : public BlobLoader
	{
	public:
		TextureBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const char* path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	private:
		void doLoadTexture2D(BlobHolder* blobHolder);
		void doLoadTextureCubeMap(BlobHolder* blobHolder);

		std::mutex m_mtx2;
	};
}