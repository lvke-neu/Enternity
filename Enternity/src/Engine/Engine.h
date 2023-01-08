/***************************************************************************************
Author: lvke
Date:2022/12/31 11:56
Description:
Engine
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "Timer/GameTimer.h"

struct GLFWwindow;
BEGIN_ENTERNITY

class Engine
{
	SINGLETON(Engine);
public:
	bool Initialize();
	void Run();
	void ShutDown();
private:
	Engine() = default; 
	~Engine();
	Engine(const Engine&) = default;
	Engine& operator=(const Engine&) = default;
private:
	GLFWwindow* m_context{ nullptr };
	GameTimer m_timer;
	bool m_userNeedShutDown = false;
};

END_ENTERNITY