#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class MeshBlobHolder;
	class ModelBlobLoader : public BlobLoader
	{
	public:
		ModelBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const char* path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	};
}