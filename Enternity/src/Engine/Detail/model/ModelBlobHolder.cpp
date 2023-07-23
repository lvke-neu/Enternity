#include "ModelBlobHolder.h"

namespace Enternity
{
	ModelBlobHolder::ModelBlobHolder(BlobLoader* blobLoader, const std::string& path) :
		BlobHolder(blobLoader, path)
	{

	}

	Asset* ModelBlobHolder::createAsset()
	{
		return nullptr;
	}
}