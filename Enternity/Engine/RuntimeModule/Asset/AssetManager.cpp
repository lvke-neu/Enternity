#include "AssetManager.h"
#include "Utility/Utility.h"
#include "Asset.h"
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

	void AssetManager::loadAssetImpl(Asset& asset)
	{
		asset.doLoad();
		asset.callBack();
	}
}