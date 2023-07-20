#include "RendererProvider.h"
#include "Engine/Detail/renderer/RendererBlobLoader.h"
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

	Renderer* RendererProvider::getRendererSync(const char* vsFullPath, const char* psFullPath)
	{
		

		return nullptr;
	}

	void RendererProvider::getRendererAsyn(const char* vsFullPath, const char* psFullPath, std::function<void(Renderer*)> callback)
	{
	
	}

	void RendererProvider::tick(void* data)
	{
		
	}
}