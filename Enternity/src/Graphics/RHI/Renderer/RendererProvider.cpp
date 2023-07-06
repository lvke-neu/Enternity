#include "RendererProvider.h"
#include "Renderer.h"
#include "RendererAsset.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Engine/Event/EventSystem.h"

namespace Enternity
{
	RendererProvider::RendererProvider()
	{
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::Tick, BIND(RendererProvider::tick));
	}

	RendererProvider::~RendererProvider()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::Tick, BIND(RendererProvider::tick));
	}

	Renderer* RendererProvider::getRendererSync(const char* vsFullPath, const char* psFullPath)
	{
		RendererAsset* vsRendererAsset = new RendererAsset(vsFullPath);
		vsRendererAsset->load(0);

		RendererAsset* psRendererAsset = new RendererAsset(psFullPath);
		psRendererAsset->load(0);

		Renderer* renderer = nullptr;
		
		if (vsRendererAsset->getLoadingState() == Asset::LoadingState::loading_state_succeeded &&
			psRendererAsset->getLoadingState() == Asset::LoadingState::loading_state_succeeded)
		{
			renderer = new Renderer(vsRendererAsset, psRendererAsset);
		}
		
		SAFE_DELETE_SET_NULL(vsRendererAsset);
		SAFE_DELETE_SET_NULL(psRendererAsset);

		return renderer;
	}

	void RendererProvider::getRendererAsyn(const char* vsFullPath, const char* psFullPath, std::function<void(Renderer*)> callback)
	{
		RendererAsset* vsRendererAsset = new RendererAsset(vsFullPath);
		vsRendererAsset->load();

		RendererAsset* psRendererAsset = new RendererAsset(psFullPath);
		psRendererAsset->load();

		m_map.push_back({ vsRendererAsset, psRendererAsset, callback });
	}

	void RendererProvider::tick(void* data)
	{
		for (auto it = m_map.begin(); it != m_map.end(); )
		{
			if (it->vsRendererAsset->getLoadingState() == Asset::LoadingState::loading_state_succeeded
				&& it->psRendererAsset->getLoadingState() == Asset::LoadingState::loading_state_succeeded)
			{
				it->callback(new Renderer(it->vsRendererAsset, it->psRendererAsset));
				SAFE_DELETE_SET_NULL(it->vsRendererAsset);
				SAFE_DELETE_SET_NULL(it->psRendererAsset);
				it = m_map.erase(it);
			}
			else
			{
				it++;
			}
		}
	}
}