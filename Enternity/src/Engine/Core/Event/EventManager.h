/***************************************************************************************
Author: lvke
Date:2023/2/14 23:29
Description:
EventManager
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include "Event.h"
#include <unordered_map>
#include <functional>

namespace Enternity
{
	class EventManager
	{
		SINGLETON(EventManager);
		PRIVATE(EventManager);
	public:
		void dispatch(IEvent* event);
	private:
		std::unordered_map<EventType, std::vector<std::function<void(IEvent*)>>> m_events;
	};
}