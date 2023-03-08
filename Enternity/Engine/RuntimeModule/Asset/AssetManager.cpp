#include "AssetManager.h"
#include "Utility/Utility.h"
#include "Core/Blob/Blob.h"
#include "Asset.h"
#include "AssetLoader.h"
#include "Core/ThreadPool/ThreadPool.h"
#include "Core/ThreadPool/ThreadPool.h"

namespace Enternity
{
	bool AssetManager::Initialize()
	{
		return true;
	}

	void AssetManager::Finalize()
	{
		for (auto& cache : m_cache)
		{
			SAFE_DELETE_SET_NULL(cache.second);
		}
	}

	void AssetManager::Tick()
	{

	}

	void AssetManager::loadAsset(Asset& asset)
	{
		ThreadPool::GetInstance().commitTask(
			[&]()
			{
				loadAssetImpl(asset);
			}
		);
	}

	void AssetManager::unLoadAsset(const std::string& assetID)
	{
		auto iter = m_cache.find(assetID);
		if (iter != m_cache.end())
		{
			SAFE_DELETE_SET_NULL(iter->second);
			m_cache.erase(iter);
		}
	}

	void AssetManager::loadAssetImpl(Asset& asset)
	{
		auto iter = m_cache.find(asset.getAssetID());
		if (iter != m_cache.end())
		{
			asset.setBlob(iter->second);
			return;
		}

		Blob* tmp = asset.getAssetLoader()->doLoad(asset.getAssetID());
		if (tmp)
		{
			m_cache[asset.getAssetID()] = tmp;
			asset.setBlob(m_cache[asset.getAssetID()]);
			return;
		}

		asset.setBlob(nullptr);
	}
}