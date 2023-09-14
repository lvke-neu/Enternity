#include "Node.h"
#include "Component.h"
#include "Common/Utility.h"

namespace Enternity
{
	Node::Node() : m_name(""), m_parent(nullptr)
	{
		m_uuid = Utility::GenerateUUID();
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

}
