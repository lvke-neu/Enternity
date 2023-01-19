/***************************************************************************************
Author: lvke
Date:2023/1/19 18:48
Description:
Interface of Panel
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "Imgui/ImguiImpl/imgui.h"
#include "Imgui/ImguiImpl/imgui_internal.h"
#include "Imgui/ImguiImpl/imgui_impl_glfw.h"
#include "Imgui/ImguiImpl/imgui_impl_opengl3.h"
#include "Event/ImguiDrawEventManager.h"

BEGIN_ENTERNITY

class IPanel : public ImguiDrawEvent
{
public:
	IPanel();
	virtual ~IPanel();
	virtual void ImguiDraw() = 0;
};

END_ENTERNITY
