#include "Vector4.h"

namespace Enternity
{
	Vector4f Vector4f::ZERO			= { 0.0f, 0.0f, 0.0f, 0.0f };
	Vector4f Vector4f::ONE			= { 1.0f, 1.0f, 1.0f, 1.0f };

	Vector4f Vector4f::DARK_COLOR   = { 0.1f, 0.1f, 0.1f, 1.0f };
	Vector4f Vector4f::RED_COLOR	= { 1.0f, 0.0f, 0.0f, 1.0f };
	Vector4f Vector4f::GREEN_COLOR	= { 0.0f, 1.0f, 0.0f, 1.0f };
	Vector4f Vector4f::BLUE_COLOR	= { 0.0f, 0.0f, 1.0f, 1.0f };

	Vector4f::Vector4f()
	{

	}

	Vector4f::Vector4f(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}
}