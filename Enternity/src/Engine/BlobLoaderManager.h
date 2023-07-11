#pragma once
#include "AssetID.h"
#include <vector>

namespace Enternity
{
	class BlobLoader;
	class BlobLoaderManager
	{
	public:
		BlobLoaderManager();
		~BlobLoaderManager();
	public:
		void registerBlobLoader(BlobLoader* blobLoader);
		BlobLoader* getBlobLoaderByAssetID(const AssetID& assetID);
	private:
		std::vector<BlobLoader*> m_blobLoaders;
	};

}