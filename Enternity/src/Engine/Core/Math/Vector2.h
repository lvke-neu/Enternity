/***************************************************************************************
Author: lvke
Date:
Description:
Vector2
****************************************************************************************/
#pragma once

namespace Enternity
{
	struct Vector2f
	{
		Vector2f();
		Vector2f(float x, float y);

		float x;
		float y;

		static Vector2f ZERO;
		static Vector2f ONE;
	};
}