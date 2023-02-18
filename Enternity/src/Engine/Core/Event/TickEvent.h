/***************************************************************************************
Author: lvke
Date:2023/2/18 11:06
Description:
TickEvent
****************************************************************************************/
#pragma once
#include "Event.h"

namespace Enternity
{
	class TickEvent : public IEvent
	{
	public:
		TickEvent(float deltaTime) :
			m_deltaTime(deltaTime)
		{

		}

		inline float getDeltaTime() { return m_deltaTime; }

		virtual EventType getEventType() override
		{
			return EventType::Tick;
		}

		virtual std::string toString() override
		{
			return "TickEvent: deltaTime = " + std::to_string(m_deltaTime);
		}
	private:
		float m_deltaTime;
	};
}