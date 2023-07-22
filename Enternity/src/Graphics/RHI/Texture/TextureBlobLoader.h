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
	};
}