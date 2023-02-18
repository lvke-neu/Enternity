/***************************************************************************************
Author: lvke
Date:2023/2/6 23:10
Description:
Vector3
****************************************************************************************/
#pragma once

namespace Enternity
{
	struct Vector3f
	{
		Vector3f();
		Vector3f(float x, float y, float z);
		Vector3f(float* data);

		float x;
		float y;
		float z;

		static Vector3f ZERO;
		static Vector3f ONE;

		Vector3f operator*(float num) const;
		void operator+=(const Vector3f& vec3);
		Vector3f operator-();
	};
}