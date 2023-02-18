/***************************************************************************************
Author: lvke
Date:2023/2/18 11:47
Description:
MouseEvent
****************************************************************************************/
#pragma once
#include "Event.h"

namespace Enternity
{
	enum class MouseCode
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	};

	class MouseEvent : public IEvent
	{
	public:
		MouseEvent(MouseCode mouseCode, float mouseX, float mouseY) :
			m_mouseCode(mouseCode), m_mouseX(mouseX), m_mouseY(mouseY)
		{

		}

		inline MouseCode getMouseCode()
		{
			return m_mouseCode;
		}

		inline float getMouseX()
		{
			return m_mouseX;
		}

		inline float getMouseY()
		{
			return m_mouseY;
		}
	private:
		MouseCode m_mouseCode;
		float m_mouseX;
		float m_mouseY;
	};

	class MousePressedEvent : public MouseEvent
	{
	public:
		MousePressedEvent(MouseCode mouseCode, float mouseX, float mouseY) : 
			MouseEvent(mouseCode, mouseX, mouseY)
		{

		}

		virtual EventType getEventType() override
		{
			return EventType::MousePressed;
		}

		virtual std::string toString() override
		{
			return "";
		}
	};

	class MouseReleasedEvent : public MouseEvent
	{
	public:
		MouseReleasedEvent(MouseCode mouseCode, float mouseX, float mouseY) :
			MouseEvent(mouseCode, mouseX, mouseY)
		{

		}

		virtual EventType getEventType() override
		{
			return EventType::MouseReleased;
		}

		virtual std::string toString() override
		{
			return "";
		}
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(MouseCode mouseCode, float mouseX, float mouseY) :
			MouseEvent(mouseCode, mouseX, mouseY)
		{

		}

		virtual EventType getEventType() override
		{
			return EventType::MouseMoved;
		}

		virtual std::string toString() override
		{
			return "";
		}
	};
}