#include "AssetLoader.h"
#include "Asset.h"
#include "Engine.h"
#include "EventSystem.h"
#include "BlobLoader.h"
#include "BlobHolder.h"
#include "BlobLoaderManager.h"

namespace Enternity
{
	AssetLoader::AssetLoader()
	{
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::Tick, BIND(AssetLoader::tick));
	}

	AssetLoader::~AssetLoader()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::Tick, BIND(AssetLoader::tick));
	}

	void AssetLoader::getAsset(const char* path, std::function<void(Asset*)> callback)
	{
		BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
		if (blobLoader)
		{
			BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
			if (blobHolder)
			{
				blobHolder->load();
				m_task.push_back({ blobHolder, callback });
			}
		}
	}
	
	void AssetLoader::tick(void* data)
	{
		for (auto it = m_task.begin(); it != m_task.end(); )
		{
			if (it->blobHolder->isLoadSucceeded())
			{
				Asset* asset = it->blobHolder->createAsset();
				asset->load(it->blobHolder);
				it->callback(asset);
				SAFE_DELETE_SET_NULL(it->blobHolder);
				it = m_task.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

}