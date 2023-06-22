#include "EventSystem.h"

namespace Enternity
{
	EventSystem::EventSystem()
	{

	}

	EventSystem::~EventSystem()
	{
		m_events.clear();
	}

	void EventSystem::registerEvent(const Event& event)
	{
		m_events.push_back(event);
	}

	void EventSystem::dispatchEvent(EventType type, void* data)
	{
		for (auto& event : m_events)
		{
			if (event.type == type)
			{
				event.callback(data);
			}
		}
	}
}