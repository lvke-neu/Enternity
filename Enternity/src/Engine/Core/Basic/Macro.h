/***************************************************************************************
Author: lvke
Date:2023/2/5 22:31
Description:
Macro
****************************************************************************************/
#pragma once
#include <CRTDBG.H>

//assert
#ifdef DEBUG
	#define  ENTERNITY_ASSERT(expr)	_ASSERTE(expr)
#else
	#define  ENTERNITY_ASSERT(expr)	((void)0)
#endif 

// singleton
#define SINGLETON(CLASS) \
	public:\
		static CLASS& GetInstance()\
		{\
			static CLASS s_instance;\
			return s_instance; \
		}
#define PRIVATE(CLASS)\
	private: \
		CLASS() = default; \
		virtual ~CLASS() = default; \
		CLASS(const CLASS&) = default; \
		CLASS& operator=(const CLASS&) = default;