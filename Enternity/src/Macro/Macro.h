/***************************************************************************************
Author: lvke
Date:2022/12/31 10:07
Description:
Macro
****************************************************************************************/
#pragma once

#define BEGIN_ENTERNITY namespace Enternity {
#define END_ENTERNITY }

#define SINGLETON(CLASS) \
	public:\
		static CLASS& GetInstance()\
		{\
			static CLASS s_instance;\
			return s_instance; \
		}