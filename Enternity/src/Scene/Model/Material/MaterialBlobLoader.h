#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class MaterialBlobLoader : public BlobLoader
	{
	public:
		MaterialBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const char* path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	};
}