#include "BlobLoaderManager.h"
#include "BlobLoader.h"
#include "Common/Macro.h"
#include "Detail/RendererBlobLoader.h"

namespace Enternity
{
	BlobLoaderManager::BlobLoaderManager()
	{
		registerBlobLoader(new RendererBlobLoader);
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
			if ((*it)->m_storagePath == blobLoader->m_storagePath)
			{
				return;
			}
		}
		m_blobLoaders.push_back(blobLoader);
	}

	BlobLoader* BlobLoaderManager::getBlobLoader(const std::string& path)
	{
		auto it = m_blobLoaders.begin();
		auto end = m_blobLoaders.end();
		for (; it != end; ++it)
		{
			BlobLoader* blobLoader = *it;
			if (0 == strncmp(blobLoader->m_storagePath.c_str(), path.c_str(), blobLoader->m_storagePath.size()))
			{
				return blobLoader;
			}
		}
		return nullptr;
	}
}