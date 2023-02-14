/***************************************************************************************
Author: lvke
Date:2023/2/14 23:30
Description:
EventManager
****************************************************************************************/
#pragma once

namespace Enternity
{
	enum class EventType
	{
		WindowResize
	};

	class IEvent
	{
	public:
		IEvent() = default;
		virtual ~IEvent() = default;

		virtual EventType getEventType() = 0;
	};
}