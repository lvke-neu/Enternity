/***************************************************************************************
Author: lvke
Date:2022/1/15 12:49
Description:
File Dialog
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include <string>

BEGIN_ENTERNITY

class FileDialog
{
public:
	static std::string OpenFile(const char* filter);
	static std::string SaveFile(const char* filter);
};

END_ENTERNITY