/***************************************************************************************
Author: lvke
Date:2022/12/31 10:07
Description:
Macro
****************************************************************************************/
#pragma once
#include <assert.h>

//namespace
#define BEGIN_ENTERNITY namespace Enternity {
#define END_ENTERNITY }

#define SINGLETON(CLASS) \
	public:\
		static CLASS& GetInstance()\
		{\
			static CLASS s_instance;\
			return s_instance; \
		}

// singleton
#define PRIVATE_FUCNTION(CLASS)\
	private: \
		CLASS() = default; \
		virtual ~CLASS() = default; \
		CLASS(const CLASS&) = default; \
		CLASS& operator=(const CLASS&) = default;
