#include "RHIAssetProvider.h"
#include "Engine/Engine.h"
#include "Engine/Event/EventSystem.h"
#include "Engine/BlobLoader.h"
#include "Engine/BlobHolder.h"
#include "Engine/BlobLoaderManager.h"

namespace Enternity
{
	RHIAssetProvider::RHIAssetProvider()
	{
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::Tick, BIND(RHIAssetProvider::tick));
	}

	RHIAssetProvider::~RHIAssetProvider()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::Tick, BIND(RHIAssetProvider::tick));
	}

	void RHIAssetProvider::getRHIAsset(const char* path, std::function<void(RHIAsset*)> callback)
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
}