#include "AssetManager.h"
#include "Utility/Utility.h"
#include "Core/Blob/Blob.h"
#include "Asset.h"
#include "AssetLoader.h"

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

	Blob* AssetManager::loadAsset(const Asset& asset)
	{
		auto iter = m_cache.find(asset.getAssetID());
		if (iter != m_cache.end())
		{
			return iter->second;
		}
		
		Blob* tmp = loadAssetImpl(asset);
		if (tmp)
		{
			m_cache[asset.getAssetID()] = tmp;
			return m_cache[asset.getAssetID()];
		}
		
		return nullptr;
	}

	Blob* AssetManager::loadAssetImpl(const Asset& asset)
	{
		return asset.getAssetLoader()->doLoad(asset.getAssetID());
	}
}