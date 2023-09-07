#pragma once
#include <string>
#include <vector>
#include <rttr/registration>

#define GET_SET(TYPE, NAME)\
	const TYPE& get_##NAME() const\
	{\
		return m_##NAME;\
	}\
	void set_##NAME(const TYPE& NAME)\
	{\
		m_##NAME = NAME;\
	}

namespace Enternity
{
	class Component
	{
	public:
		GET_SET(bool, enable);
		GET_SET(int, tag);
	private:
		bool m_enable;
		int m_tag;
	};

	class Node
	{
	public:
		Node();
		virtual ~Node();
	public:
		GET_SET(std::string, name);
		GET_SET(std::string, uuid);
		GET_SET(Component, component);
		GET_SET(unsigned int, uint);

		void addToParent(Node* node);
		const std::vector<Node*>& getChilds() const;
	private:
		std::string m_name;
		std::string m_uuid;
		Component m_component;
		unsigned int m_uint;

		Node* m_parent;
		std::vector<Node*> m_childs;
		
	};

	inline const std::vector<Node*>& Node::getChilds() const
	{
		return m_childs;
	}
}


RTTR_REGISTRATION
{
	rttr::registration::class_<Enternity::Component>("Component")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("m_enable", &Enternity::Component::get_enable, &Enternity::Component::set_enable)
		.property("m_tag", &Enternity::Component::get_tag, &Enternity::Component::set_tag);


	rttr::registration::class_<Enternity::Node>("Node")
		.constructor<>()
		(
			rttr::policy::ctor::as_raw_ptr
		)
		.property("m_name", &Enternity::Node::get_name, &Enternity::Node::set_name)
		.property("m_uuid", &Enternity::Node::get_uuid, &Enternity::Node::set_uuid)
		.property("m_component", &Enternity::Node::get_component, &Enternity::Node::set_component)
		.property("m_uint", &Enternity::Node::get_uint, &Enternity::Node::set_uint);
}