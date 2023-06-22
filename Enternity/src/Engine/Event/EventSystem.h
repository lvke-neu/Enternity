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
		void registerEvent(EventType type, std::function<void(void*)> callback);
		void registerEvent(const Event& event);
		void unRegisterEvent(EventType type, std::function<void(void*)> callback);
		void unRegisterEvent(const Event& event);
		void dispatchEvent(EventType type, void* data);
	public:
		bool isKeyPressed(KeyCode keyCode);
	private:
		std::vector<Event> m_events;
		std::unordered_map<KeyCode, bool> m_keyTriggers;
	};

}