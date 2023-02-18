/***************************************************************************************
Author: lvke
Date:2023/2/14 23:29
Description:
EventManager
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <unordered_map>
#include <functional>

namespace Enternity
{
	enum class KeyCode;
	enum class EventType;
	class IEvent;
	class EventManager
	{
		SINGLETON(EventManager);
		PRIVATE(EventManager);
	public:
		void registry(EventType eventType, std::function<void(IEvent*)> func);
		void unRegistry(EventType eventType, std::function<void(IEvent*)> func);
		void dispatch(IEvent* event);
	public:
		bool isKeyPressed(KeyCode keyCode);
	private:
		std::unordered_map<EventType, std::vector<std::function<void(IEvent*)>>> m_events;
		std::unordered_map<KeyCode, bool> m_keyTriggers;
	};
}