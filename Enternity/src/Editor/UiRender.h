#pragma once
#include "Common/Macro.h"

struct GLFWwindow;
namespace Enternity
{
	class UiRender
	{
	public:
		UiRender(GLFWwindow* context);
		~UiRender();
		void onUpdatetime();
	private:
		void setDarkThemeColors();
	};
}