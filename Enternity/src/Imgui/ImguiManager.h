/***************************************************************************************
Author: lvke
Date:2023/1/1 12:11
Description:
Imgui Manager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "Panels/ViewportPanel.h"
#include "Panels/ViewportPanel2.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"
#include "Panels/StatsPanel.h"
#include "Panels/PlayButtonPanel.h"

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

	ViewportPanel* GetViewportPanel();

	SceneHierarchyPanel* GetSceneHierarchyPanel();
private:
	void Ui_MenuBar();

	void ShowDockSpace(bool* p_open);
	void SetDarkThemeColors();


	ViewportPanel* m_ViewportPanel{ nullptr };
	ViewportPanel2* m_ViewportPanel2{ nullptr };
	SceneHierarchyPanel* m_SceneHierarchyPanel{ nullptr };
	ContentBrowserPanel* m_ContentBrowserPanel{ nullptr };
	StatsPanel* m_StatsPanel{ nullptr };
	PlayButtonPanel* m_PlayButtonPanel{ nullptr };
};

END_ENTERNITY