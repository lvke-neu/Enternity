#include "Vector2.h"

namespace Enternity
{
	Vector2f Vector2f::ZERO = { 0.0f, 0.0f };
	Vector2f Vector2f::ONE  = { 1.0f, 1.0f };

	Vector2f::Vector2f()
	{

	}

	Vector2f::Vector2f(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
}