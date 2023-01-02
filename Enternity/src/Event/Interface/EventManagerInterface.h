/***************************************************************************************
Author: lvke
Date: 2023/1/2 15:35
Description:
EventManager Interface
****************************************************************************************/
#pragma once
#include "Macro/Macro.h"
#include <vector>

BEGIN_ENTERNITY

class IEvent
{
public:
	IEvent() = default;
	virtual ~IEvent() = default;
};

class IEventManager
{
public:
	void RegisterEvent(IEvent* event);
	void UnRegisterEvent(IEvent* event);
protected:
	std::vector<IEvent*> m_events;
};

END_ENTERNITY