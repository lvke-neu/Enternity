#include "Component.h"
#include "Node.h"

namespace Enternity
{
	Component::Component() : m_node(nullptr)
	{

	}

	Component::~Component()
	{

	}

	void Component::addToNode(Node* node)
	{
		if (!node)
		{
			return;
		}

		removeFromNode();
		node->addComponent(this);
		m_node = node;
	}

	void Component::removeFromNode()
	{
		if (m_node)
		{
			m_node->removeComponent(this);
			m_node = nullptr;
		}
	}
}