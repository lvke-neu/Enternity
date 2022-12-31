/***************************************************************************************
Author: lvke
Date:2022/12/31 9:51
Description:
Opengl Window
****************************************************************************************/
#pragma once
#include "Macro/Macro.h"

BEGIN_ENTERNITY

class OpenglWindow
{
public:
	OpenglWindow();
	OpenglWindow(unsigned int width, unsigned int height, const char* title);
	~OpenglWindow();

	void Run();
private:
	void Initialize();
private:
	unsigned int m_width;
	unsigned int m_height;
	const char* m_title;
};

END_ENTERNITY