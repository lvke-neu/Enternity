#include "TickEventManager.h"

namespace Enternity
{
	void TickEventManager::NotifyTick(float deltaTime)
	{
		for (auto& event : m_events)
		{
			if (dynamic_cast<TickEvent*>(event))
			{
				dynamic_cast<TickEvent*>(event)->tick(deltaTime);
			}
		}
	}
}