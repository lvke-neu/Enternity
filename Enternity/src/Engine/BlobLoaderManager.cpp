#include "BlobLoaderManager.h"
#include "BlobLoader.h"
#include "Log.h"
#include "Common/Macro.h"

namespace Enternity
{
	BlobLoaderManager::BlobLoaderManager()
	{

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

	BlobLoader* BlobLoaderManager::getBlobLoader(const char* path)
	{
		auto it = m_blobLoaders.begin();
		auto end = m_blobLoaders.end();
		for (; it != end; ++it)
		{
			BlobLoader* blobLoader = *it;
			if (0 == strncmp(blobLoader->m_storagePath.c_str(), path, blobLoader->m_storagePath.size()))
			{
				return blobLoader;
			}
		}

		LOG_ERROR("GetBlobLoader failed:{0}", path);

		return nullptr;
	}
}