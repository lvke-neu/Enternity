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
		void registerEvent(const Event& event);
		void dispatchEvent(EventType type, void* data);
	private:
		std::vector<Event> m_events;
	};

}