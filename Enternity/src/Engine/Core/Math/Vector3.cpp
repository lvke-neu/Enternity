#include "Vector3.h"

namespace Enternity
{
	Vector3f Vector3f::ZERO = { 0.0f, 0.0f, 0.0f };
	Vector3f Vector3f::ONE  = { 1.0f, 1.0f, 1.0f };

	Vector3f::Vector3f()
	{

	}

	Vector3f::Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
}