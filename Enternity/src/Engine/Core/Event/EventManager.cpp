#include "EventManager.h"

namespace Enternity
{
	void EventManager::dispatch(IEvent* event)
	{
		for (auto func : m_events[event->getEventType()])
		{
			func(event);
		}
	}
}