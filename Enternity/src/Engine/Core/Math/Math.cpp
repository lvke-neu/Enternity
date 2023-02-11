#include "Math.h"

namespace Enternity
{
	float Math::Radian(float degree)
	{
		return degree * PI / 180.0f;
	}

	float Math::Degree(float radian)
	{
		return 180.0f * radian / PI;
	}
}