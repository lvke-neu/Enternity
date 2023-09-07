#include "Node.h"
#include "Common/Utility.h"
#include "Common/Macro.h"

namespace Enternity
{
	Node::Node() : m_name(""), m_parent(nullptr)
	{
		m_uuid = Utility::GenerateUUID();
		m_childs.clear();
	}

	Node::~Node()
	{
		for (auto& child : m_childs)
		{
			SAFE_DELETE_SET_NULL(child);
		}
	}

	void Node::addToParent(Node* node)
	{
		if (node)
		{
			node->m_childs.emplace_back(this);
			m_parent = node;
		}
	}
}
