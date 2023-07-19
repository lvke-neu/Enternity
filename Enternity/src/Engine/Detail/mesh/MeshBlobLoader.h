#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class MeshBlobLoader : public BlobLoader
	{
	public:
		MeshBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const std::string& path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	private:
		void assimpLoad(BlobHolder* blobHolder);
	};
}