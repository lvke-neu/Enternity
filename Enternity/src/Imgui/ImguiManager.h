/***************************************************************************************
Author: lvke
Date:2023/1/1 12:11
Description:
Imgui Manager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "Imgui/ImguiImpl/imgui.h"
#include "Imgui/ImguiImpl/imgui_impl_glfw.h"
#include "Imgui/ImguiImpl/imgui_impl_opengl3.h"

struct GLFWwindow;
BEGIN_ENTERNITY

class ImguiManager
{
	SINGLETON(ImguiManager);
	PRIVATE_FUCNTION(ImguiManager);
public:
	void Initialize(GLFWwindow* context);
	void Draw();
	void Release();
};

END_ENTERNITY