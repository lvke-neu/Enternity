#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class MeshBlobHolder;
	class MeshBlobLoader : public BlobLoader
	{
	public:
		MeshBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const char* path);
		virtual void doLoad(BlobHolder* blobHolder) override;
	private:
		void loadCube(MeshBlobHolder* meshBlobHolder);
		void loadPlane(MeshBlobHolder* meshBlobHolder);
	};
}