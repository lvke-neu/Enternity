/***************************************************************************************
Author: lvke
Date:2023/2/11 21:34
Description:
Math
****************************************************************************************/
#pragma once
#include <cmath>

namespace Enternity
{	
	const float PI = 3.141592f;
	class Math
	{
	public:
		//degree to radian
		static float Radian(float degree);
		//radian to degree
		static float Degree(float radian);
	};
}