/***************************************************************************************
Author: lvke
Date: Date: 2023/1/10 23:07
Description:
ImguiDrawEvent Manager
****************************************************************************************/
#pragma once
#include "Interface/EventManagerInterface.h"

BEGIN_ENTERNITY

class ImguiDrawEvent : public virtual IEvent
{
public:
	virtual void ImguiDraw() = 0;
};

class ImguiDrawEventManager : public IEventManager
{
	SINGLETON(ImguiDrawEventManager);
	PRIVATE_FUCNTION(ImguiDrawEventManager);
public:
	void NotifyImguiDraw();
};

END_ENTERNITY