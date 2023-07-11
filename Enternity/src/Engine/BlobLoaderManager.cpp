#include "BlobLoaderManager.h"
#include "BlobLoader.h"
#include "Detail/ShaderBlobLoader.h"
#include "Common/Macro.h"

namespace Enternity
{
	BlobLoaderManager::BlobLoaderManager()
	{
		registerBlobLoader(new ShaderBlobLoader);
	}

	BlobLoaderManager::~BlobLoaderManager()
	{
		auto it = m_blobLoaders.begin();
		auto end = m_blobLoaders.end();
		for (; it != end; ++it)
		{
			SAFE_DELETE_SET_NULL(*it);
		}
	}

	void BlobLoaderManager::registerBlobLoader(BlobLoader* blobLoader)
	{
		if (!blobLoader)
		{
			return;
		}

		auto it = m_blobLoaders.begin();
		auto end = m_blobLoaders.end();
		for (; it != end; ++it)
		{
			if ((*it)->m_assetID.m_path == blobLoader->m_assetID.m_path)
			{
				return;
			}
		}
		m_blobLoaders.push_back(blobLoader);
	}

	BlobLoader* BlobLoaderManager::getBlobLoaderByAssetID(const AssetID& assetID)
	{
		auto it = m_blobLoaders.begin();
		auto end = m_blobLoaders.end();
		for (; it != end; ++it)
		{
			BlobLoader* blobLoader = *it;
			if (0 == strncmp(blobLoader->m_assetID.m_path.c_str(), assetID.m_path.c_str(), blobLoader->m_assetID.m_path.size()))
			{
				return blobLoader;
			}
		}
		return nullptr;
	}
}