#include "EventManagerInterface.h"

namespace Enternity
{

	void IEventManager::RegisterEvent(IEvent* event)
	{
		UnRegisterEvent(event);
		m_events.push_back(event);
	}

	void IEventManager::UnRegisterEvent(IEvent* event)
	{
		for (auto iter = m_events.begin(); iter != m_events.end();)
		{
			if (*iter == event)
			{
				iter = m_events.erase(iter);
				if (iter == m_events.end())
					break;
			}
			else
				iter++;
		}
	}

}
