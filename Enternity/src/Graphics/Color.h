#pragma once
#include "Engine/Reference.h"

namespace Enternity
{
	class Color : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		Color();
		Color(float r, float g, float b, float a);
	public:
		GET_CLASS_NAME(Color);
	public:
		GET_SET(float, r);
		GET_SET(float, g);
		GET_SET(float, b);
		GET_SET(float, a);
	public:
		float* toPointer();
	private:
		float m_r;
		float m_g;
		float m_b;
		float m_a;
	};

	inline float* Color::toPointer()
	{
		return &m_r;
	}
}