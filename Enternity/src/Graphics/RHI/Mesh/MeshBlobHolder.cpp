#include "MeshBlobHolder.h"
#include "Mesh.h"

namespace Enternity
{
	MeshBlobHolder::MeshBlobHolder(BlobLoader* blobLoader, const std::string& path) : 
		BlobHolder(blobLoader, path)
	{

	}

	Asset* MeshBlobHolder::createAsset()
	{
		return new Mesh;
	}
}

