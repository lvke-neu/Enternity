#pragma once
#include "Common/Macro.h"
#include <string>
#include <rttr/registration>

namespace Enternity
{
	class Node;
	class Component
	{
	public:
		Component();
		virtual ~Component();
	public:
		GET(Node*, node);
		GET_SET(std::string, name);
		GET_SET(bool, enable);
		void addToNode(Node* node);
		void removeFromNode();
	protected:
		Node* m_node;
		std::string m_name;
		bool m_enable;
	};

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Component>("Component")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("name", &Component::get_name, &Component::set_name)
			.property("enable",&Component::get_enable, &Component::set_enable);
	}
}

