#include "Node.h"
#include "Common/Utility.h"
#include "Common/Macro.h"

namespace Enternity
{
	Node::Node() : m_name(""), m_parent(nullptr)
	{
		m_uuid = Utility::GenerateUUID();
	}

	Node::~Node()
	{
		removeFromParent();
		for (auto child : m_childs)
		{
			SAFE_DELETE_SET_NULL(child);
		}
		m_childs.clear();
	}

	void Node::addToParent(Node* node)
	{
		if (node)
		{
			removeFromParent();
			node->m_childs.insert(this);
			m_parent = node;
		}
	}

	void Node::removeFromParent()
	{
		if (m_parent)
		{
			auto iter = m_parent->m_childs.find(this);
			if (iter != m_parent->m_childs.end())
			{
				m_parent->m_childs.erase(iter);
			}
		}

		m_parent = nullptr;
	}
}
