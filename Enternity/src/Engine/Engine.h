/***************************************************************************************
Author: lvke
Date:2023/2/5 22:50
Description:
Engine
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class OpenglWindow;
	class FrameTimer;
	class Engine
	{
		SINGLETON(Engine);
		PRIVATE(Engine);
	public:
		void initialize();
		void uninitialize();
		void run();
	private:
		OpenglWindow* m_window{ nullptr };
		FrameTimer* m_timer{ nullptr };
	};
}