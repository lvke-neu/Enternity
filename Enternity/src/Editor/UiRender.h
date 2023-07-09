#pragma once
#include "Common/Macro.h"

struct GLFWwindow;
namespace Enternity
{
	class ViewPortPanel;
	class StatePanel;
	class ScenePanel;
	class AssetPanel;
	class UiRender
	{
	public:
		UiRender(GLFWwindow* context);
		~UiRender();
		void tick();
	private:
		void setDarkThemeColors();
		void drawDockSpace();
	private:
		ViewPortPanel* m_viewPortPanel{ nullptr };
		StatePanel* m_statePanel{ nullptr };
		ScenePanel* m_scenePanel{ nullptr };
		AssetPanel* m_assetPanel{ nullptr };
	};
}