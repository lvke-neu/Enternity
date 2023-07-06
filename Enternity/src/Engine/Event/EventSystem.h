#pragma once
#include "EventDefine.h"
#include <vector>

namespace Enternity
{
	class EventSystem
	{
		friend class Engine;
	private:
		EventSystem();
		~EventSystem();
	public:
		void registerEvent(Event::EventType type, std::function<void(void*)> callback);
		void registerEvent(const Event& event);
		void unRegisterEvent(Event::EventType type, std::function<void(void*)> callback);
		void unRegisterEvent(const Event& event);
		void dispatchEvent(Event::EventType type, void* data);
		void setIsDispatchInputEvent(bool flag);
	public:
		bool isKeyPressed(KeyCode keyCode);
	private:
		std::vector<Event> m_events;
		std::unordered_map<KeyCode, bool> m_keyTriggers;
		bool m_bDispatchInputEvent{ true };
	};

	inline void EventSystem::setIsDispatchInputEvent(bool flag)
	{
		m_bDispatchInputEvent = flag;
	}

}