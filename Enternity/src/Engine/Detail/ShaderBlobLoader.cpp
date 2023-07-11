#include "ShaderBlobLoader.h"
#include "ShaderBlobHolder.h"

namespace Enternity
{
	ShaderBlobLoader::ShaderBlobLoader() : BlobLoader(AssetID("shader://"))
	{

	}

	ShaderBlobLoader::~ShaderBlobLoader()
	{
	
	}

	BlobHolder* ShaderBlobLoader::createBlobHolder(const AssetID& assetID)
	{
		return new ShaderBlobHolder(assetID);
	}
}