/***************************************************************************************
Author: lvke
Date:2022/1/1 12:11
Description:
Imgui Manager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"

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