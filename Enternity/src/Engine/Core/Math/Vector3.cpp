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

	Vector3f::Vector3f(float* data)
	{
		this->x = *data;
		this->y = *(data + 1);
		this->z = *(data + 2);
	}

	Vector3f Vector3f::operator*(float num) const
	{
		Vector3f vec3(this->x, this->y, this->z);
		vec3.x *= num;
		vec3.y *= num;
		vec3.z *= num;

		return vec3;
	}

	Vector3f Vector3f::operator-()
	{
		return Vector3f(-this->x, -this->y, -this->z);
	}

	void Vector3f::operator+=(const Vector3f& vec3)
	{
		this->x += vec3.x;
		this->y += vec3.y;
		this->z += vec3.z;
	}
}