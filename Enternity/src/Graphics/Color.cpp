#include "Color.h"

namespace Enternity
{
	Color::Color() : m_r(1.0f), m_g(1.0f), m_b(1.0f), m_a(1.0f)
	{

	}

	Color::Color(float r, float g, float b, float a) : 
		m_r(r), m_g(g), m_b(b), m_a(a)
	{

	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Color>("Color")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("r", &Color::get_r, &Color::set_r)
			.property("g", &Color::get_g, &Color::set_g)
			.property("b", &Color::get_b, &Color::set_b)
			.property("a", &Color::get_a, &Color::set_a);

	}
}