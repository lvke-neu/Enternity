#include "EventManager.h"
#include "Core/Basic/Macro.h"
#include "Core/Log/Log.h"

namespace Enternity
{
	void EventManager::registry(EventType eventType, std::function<void(IEvent*)> func)
	{
		unRegistry(eventType, func);
		m_events[eventType].push_back(func);
	}

	void EventManager::unRegistry(EventType eventType, std::function<void(IEvent*)> _func)
	{
		auto& events = m_events[eventType];
		for (auto iter = events.begin(); iter != events.end(); iter++)
		{
			if ((*iter).target_type() == _func.target_type())
			{
				events.erase(iter);
				break;
				
			}
		}
	}

	void EventManager::dispatch(IEvent* event)
	{
		ENTERNITY_ASSERT(event != nullptr);

		LOG_INFO(event->toString());

		for (auto func : m_events[event->getEventType()])
		{
			func(event);
		}
	}
}