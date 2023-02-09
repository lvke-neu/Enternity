/***************************************************************************************
Author: lvke
Date:2023/2/6 22:50
Description:
RenderSystem
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include "Core/Math/Vector4.h"

namespace Enternity
{
	class RenderSystem
	{
		SINGLETON(RenderSystem);
		PRIVATE(RenderSystem);
	public:
		void initialize();
		void uninitialize();
	public:
		void clear(const Vector4f& vec4);
	};
}