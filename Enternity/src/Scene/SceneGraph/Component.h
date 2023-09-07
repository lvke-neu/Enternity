//#pragma once
//#include <rttr/registration>
//
//#define GET_SET(TYPE, NAME)\
//	const TYPE& get_##NAME() const\
//	{\
//		return m_##NAME;\
//	}\
//	void set_##NAME(const TYPE& NAME)\
//	{\
//		m_##NAME = NAME;\
//	}
//
//namespace Enternity
//{
//	class Component
//	{
//	public:
//		Component();
//		GET_SET(bool, enable);
//		GET_SET(int, tag);
//	private:
//		bool m_enable;
//		int m_tag;
//	};
//}
//
//
//RTTR_REGISTRATION
//{
//	rttr::registration::class_<Enternity::Component>("Component")
//		.constructor<>()
//		(
//			rttr::policy::ctor::as_raw_ptr
//		)
//		.property("m_enable", &Enternity::Component::get_enable, &Enternity::Component::set_enable)
//		.property("m_tag", &Enternity::Component::get_tag, &Enternity::Component::set_tag);
//}
