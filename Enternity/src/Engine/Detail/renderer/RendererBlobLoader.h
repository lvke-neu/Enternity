#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class RendererBlobLoader : public BlobLoader
	{
	public:
		RendererBlobLoader();
	public:
		virtual void doLoad(BlobHolder* blobHolder) override;
		virtual BlobHolder* createBlobHolder(const std::string& path) override;
	};
}