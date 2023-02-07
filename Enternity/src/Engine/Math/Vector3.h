/***************************************************************************************
Author: lvke
Date:2023/2/6 22:59
Description:
Matrix 4x4  row-major
****************************************************************************************/
#pragma once

namespace Enternity
{
	struct Vector3f
	{
		Vector3f();
		Vector3f(float x, float y, float z);

		float x;
		float y;
		float z;

		static Vector3f ZERO;
		static Vector3f ONE;
	};
}