#include "Node.h"

Node::Node() : 
	m_name(""),
	m_parent(nullptr)
{
	//m_uuid = Utility::GenerateUUID();
	m_childs.clear();
}

Node::~Node()
{

}

void Node::addChild(std::shared_ptr<Node> child)
{
	if (!child || this == child.get())
	{
		return;
	}

	auto iter = std::find(m_childs.begin(), m_childs.end(), child);
	if (iter != m_childs.end())
	{
		return;
	}

	child->removeFromParent();
	m_childs.emplace_back(child);
	child->m_parent = std::shared_ptr<Node>(this);
}

void Node::removeChild(std::shared_ptr<Node> child)
{
	if (!child)
	{
		return;
	}

	auto iter = std::find(m_childs.begin(), m_childs.end(), child);
	if (iter == m_childs.end())
	{
		return;
	}

	m_childs.erase(iter);
	//child->m_parent = nullptr;
}

void Node::removeFromParent()
{
	if (m_parent)
	{
		m_parent->removeChild(std::shared_ptr<Node>(this));
	}
}
