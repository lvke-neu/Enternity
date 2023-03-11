/***************************************************************************************
Author: lvke
Date:2023/2/9 23:56
Description:
UiRenderSystem
****************************************************************************************/
#pragma once
#include "Utility/Utility.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

struct GLFWwindow;
namespace Enternity
{
	class GUIRender
	{
		SINGLETON(GUIRender);
	public:
		void Initialize(GLFWwindow* context);
		void Finalize();
		void Tick();
	private:
		void setDarkThemeColors();
	};
}