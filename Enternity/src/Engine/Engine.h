/***************************************************************************************
Author: lvke
Date:2023/2/5 22:50
Description:
Engine
****************************************************************************************/
#pragma once
#include "Basic/Macro.h"

namespace Enternity
{
	class Engine
	{
		SINGLETON(Engine);
		PRIVATE(Engine);
	public:
		void initialize();
		void uninitialize();
	};
}