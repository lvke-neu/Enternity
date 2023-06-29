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

	void EventSystem::registerEvent(EventType type, std::function<void(void*)> callback)
	{
		Event event{ type, callback };
		registerEvent(event);
	}

	void EventSystem::unRegisterEvent(EventType type, std::function<void(void*)> callback)
	{
		Event event{ type, callback };
		unRegisterEvent(event);
	}

	void EventSystem::unRegisterEvent(const Event& event)
	{
		for (auto iter = m_events.begin(); iter != m_events.end(); iter++)
		{
			if (iter->type == event.type && iter->callback.target_type() == event.callback.target_type())
			{
				m_events.erase(iter);
				break;
			}
		}
	}

	void EventSystem::dispatchEvent(EventType type, void* data)
	{
		if (m_bDispatchInputEvent == false && (
			type == EventType::KeyPressed ||
			type == EventType::KeyReleased ||
			type == EventType::MousePressed ||
			type == EventType::MouseReleased ||
			type == EventType::MouseMoved))
		{
			m_keyTriggers.clear();
			return;
		}

		if (type == EventType::KeyPressed)
		{
			m_keyTriggers[*(KeyCode*)data] = true;
		}
		else if (type == EventType::KeyReleased)
		{
			m_keyTriggers[*(KeyCode*)data] = false;
		}

		for (auto& event : m_events)
		{
			if (event.type == type)
			{
				event.callback(data);
			}
		}
	}

	bool EventSystem::isKeyPressed(KeyCode keyCode)
	{
		return m_keyTriggers[keyCode];
	}
}