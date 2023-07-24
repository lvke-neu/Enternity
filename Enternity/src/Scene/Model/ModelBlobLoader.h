#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class ModelBlobLoader : public BlobLoader
	{
	public:
		ModelBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const std::string& path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	};
}