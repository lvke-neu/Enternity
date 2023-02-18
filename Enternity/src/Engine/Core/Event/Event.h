/***************************************************************************************
Author: lvke
Date:2023/2/14 23:30
Description:
EventManager
****************************************************************************************/
#pragma once
#include <string>

namespace Enternity
{
	enum class EventType
	{
		WindowResize,
		KeyPressed, KeyReleased, MousePressed, MouseReleased, MouseMoved,
		Tick
	};

	class IEvent
	{
	public:
		IEvent() = default;
		virtual ~IEvent() = default;

		virtual EventType getEventType() = 0;
		virtual std::string toString() = 0;
	};

#define BIND_FUNC(func) \
	std::bind(&func, this, std::placeholders::_1)

}