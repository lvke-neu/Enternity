#include "RendererProvider.h"
#include "Renderer.h"
#include "RendererBlobHolder.h"
#include "RendererBlobLoader.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoaderManager.h"
#include "Engine/Event/EventSystem.h"

namespace Enternity
{
	RendererProvider::RendererProvider()
	{
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::Tick, BIND(RendererProvider::tick));
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new RendererBlobLoader);
	}

	RendererProvider::~RendererProvider()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::Tick, BIND(RendererProvider::tick));
	}

	Renderer* RendererProvider::getRenderer(const char* path)
	{
		BlobLoader* blobLoader = Engine::GetInstance().getBlobLoaderManager()->getBlobLoader(path);
		if (blobLoader)
		{
			BlobHolder* blobHolder = blobLoader->createBlobHolder(path);
			if (blobHolder)
			{
				blobHolder->load();

				
			}
		}
		return nullptr;
	}

	void RendererProvider::tick(void* data)
	{
		
	}
}