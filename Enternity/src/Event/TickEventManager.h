/***************************************************************************************
Author: lvke
Date: Date: 2023/1/2 15:47
Description:
TickEvent Manager
****************************************************************************************/
#pragma once
#include "Interface/EventManagerInterface.h"

BEGIN_ENTERNITY

class TickEvent : public virtual IEvent
{
public:
    virtual void tick(float deltaTime) = 0;
};

class TickEventManager : public IEventManager
{
	SINGLETON(TickEventManager);
	PRIVATE_FUCNTION(TickEventManager);
public:
    void NotifyTick(float deltaTime);
};

END_ENTERNITY