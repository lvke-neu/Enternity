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

	void EventSystem::registerEvent(Event::EventType type, std::function<void(void*)> callback)
	{
		Event event{ type, callback };
		registerEvent(event);
	}

	void EventSystem::unRegisterEvent(Event::EventType type, std::function<void(void*)> callback)
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

	void EventSystem::dispatchEvent(Event::EventType type, void* data)
	{
		if (m_bDispatchInputEvent == false && (
			type == Event::EventType::KeyPressed ||
			type == Event::EventType::KeyReleased ||
			type == Event::EventType::MousePressed ||
			type == Event::EventType::MouseReleased ||
			type == Event::EventType::MouseMoved))
		{
			m_keyTriggers.clear();
			return;
		}

		if (type == Event::EventType::KeyPressed)
		{
			m_keyTriggers[*(KeyCode*)data] = true;
		}
		else if (type == Event::EventType::KeyReleased)
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