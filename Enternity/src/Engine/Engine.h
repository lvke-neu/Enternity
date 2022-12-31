/***************************************************************************************
Author: lvke
Date:2022/12/31 11:56
Description:
Engine
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "Timer/GameTimer.h"

BEGIN_ENTERNITY

class Engine
{
	SINGLETON(Engine);
	PRIVATE_FUCNTION(Engine);
public:
	void Initialize();
	void Tick();
	float GetFps();
private:
	GameTimer m_timer;
};

END_ENTERNITY