/***************************************************************************************
Author: lvke
Date:2022/12/31 9:51
Description:
Opengl Window
****************************************************************************************/
#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include "Macro/Macro.h"

BEGIN_ENTERNITY

class OpenglWindow
{
public:
	struct WindowDescription
	{
		unsigned int width;
		unsigned int height;
		std::string title;
	};
public:
	OpenglWindow();
	OpenglWindow(const WindowDescription& widowDesc);
	~OpenglWindow();

	bool Initialize();
	void Run();
private:
	WindowDescription m_widowDesc{ 800, 600, "OpenglWindow" };
	GLFWwindow* m_context{ nullptr };
};

END_ENTERNITY