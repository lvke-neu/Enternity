/***************************************************************************************
Author: lvke
Date:2023/2/9 23:56
Description:
UiRenderSystem
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"

namespace Enternity
{
	class OpenglWindow;
	class UiRenderSystem
	{
		SINGLETON(UiRenderSystem);
		PRIVATE(UiRenderSystem);
	public:
		void initialize(OpenglWindow* window);
		void uninitialize();
		void tick();
	private:
		void setDarkThemeColors();
	};
}