#pragma once
#include "AssetID.h"

namespace Enternity
{
	class BlobHolder;
	class BlobLoader
	{
		friend class BlobLoaderManager;
	public:
		BlobLoader(const AssetID& assetID);
		virtual ~BlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const AssetID& assetID) = 0;
	private:
		AssetID m_assetID;
	};
}