/***************************************************************************************
Author: lvke
Date:2023/2/8 22:55
Description:
Vector4
****************************************************************************************/
#pragma once

namespace Enternity
{
	struct Vector4f
	{
		Vector4f();
		Vector4f(float x, float y, float z, float w);

		float x;
		float y;
		float z;
		float w;

		static Vector4f ZERO;
		static Vector4f ONE;
		static Vector4f DARK_COLOR;
		static Vector4f RED_COLOR;
		static Vector4f GREEN_COLOR;
		static Vector4f BLUE_COLOR;
	};
}