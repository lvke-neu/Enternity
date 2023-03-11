#include "Math.h"

namespace Enternity
{
	namespace Math
	{
		double AngleToRadian(double angle)
		{
			return angle * PI / 180.0;
		}

		double RadianToAngle(double radian)
		{
			return 180.0 * radian / PI;
		}
	}
}