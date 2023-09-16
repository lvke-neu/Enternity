#include "Node.h"
#include "Component.h"

namespace Enternity
{
	Node::Node() : m_name(""), m_parent(nullptr)
	{
		m_childs.clear();
	}

	Node::~Node()
	{
		removeFromParent();
		auto tmpChilds = m_childs;
		for (auto& child : tmpChilds)
		{
			SAFE_DELETE_SET_NULL(child);
		}
		m_childs.clear();

		for (auto& component : m_components)
		{
			SAFE_DELETE_SET_NULL(component);
		}
		m_components.clear();
	}

	void Node::addToParent(Node* parent)
	{
		if (!parent || this == parent)
		{
			return;
		}

		auto iter = std::find(parent->m_childs.begin(), parent->m_childs.end(), this);
		if (iter != parent->m_childs.end())
		{
			return;
		}

		removeFromParent();
		parent->m_childs.emplace_back(this);
		m_parent = parent;
	}

	void Node::removeFromParent()
	{
		if (!m_parent)
		{
			return;
		}

		auto iter = std::find(m_parent->m_childs.begin(), m_parent->m_childs.end(), this);
		if (iter == m_parent->m_childs.end())
		{
			return;
		}

		m_parent->m_childs.erase(iter);
		m_parent = nullptr;
	}

	void Node::addComponent(Component* component)
	{
		if (!component)
		{
			return;
		}

		auto iter = std::find(m_components.begin(), m_components.end(), component);
		if (iter != m_components.end())
		{
			return;
		}

		m_components.emplace_back(component);
	}

	void Node::removeComponent(Component* component)
	{
		if (!component)
		{
			return;
		}

		auto iter = std::find(m_components.begin(), m_components.end(), component);
		if (iter == m_components.end())
		{
			return;
		}

		m_components.erase(iter);
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Node>("Node")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("name", &Node::get_name, &Node::set_name);
	}
}
