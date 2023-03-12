/***************************************************************************************
Author: lvke
Date: Date: 2023/1/2 15:47
Description:
TickEvent Manager
****************************************************************************************/
#pragma once
#include "Interface/EventManagerInterface.h"
#include "Utility/Utility.h"

namespace Enternity
{

	class TickEvent : public virtual IEvent
	{
	public:
		virtual void tick(float deltaTime) = 0;
	};

	class TickEventManager : public IEventManager
	{
		SINGLETON(TickEventManager);
	public:
		void NotifyTick(float deltaTime);
	};

}