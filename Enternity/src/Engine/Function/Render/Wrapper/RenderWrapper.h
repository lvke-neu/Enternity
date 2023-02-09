/***************************************************************************************
Author: lvke
Date:
Description:
Render Wrapper
****************************************************************************************/
#pragma once
#include "VertexBuffer.h"

namespace Enternity
{
	class RenderWrapper
	{
	public:
		template<typename T>
		static T* Create();
	};

	template<typename T>
	T* RenderWrapper::Create()
	{
		return new T;
	}
}