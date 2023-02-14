/***************************************************************************************
Author: lvke
Date:2023/2/14 23:36
Description:
WindowResizeEvent
****************************************************************************************/
#pragma once
#include "Event.h"

namespace Enternity
{
	class WindowResizeEvent : public IEvent
	{
	public:
		WindowResizeEvent(int width, int height) :
			m_width(width), m_height(height)
		{

		}
		
		inline int getWidth() { return m_width; }
		inline int getHeight() { return m_height; }

		virtual EventType getEventType() override
		{
			return EventType::WindowResize;
		}
	private:
		int m_width;
		int m_height;
	};
}