/***************************************************************************************
Author: lvke
Date:2023/1/1 12:11
Description:
Imgui Manager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "Imgui/ImguiImpl/imgui.h"
#include "Imgui/ImguiImpl/imgui_internal.h"
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
private:
	void ShowDockSpace(bool* p_open);
	void SetDarkThemeColors();

	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_GizmoType = -1;
	ImVec2 m_ViewportBounds[2];
};

END_ENTERNITY