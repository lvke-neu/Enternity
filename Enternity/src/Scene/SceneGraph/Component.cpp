#include "Component.h"


namespace Enternity
{
	Component::Component() : 
		m_enable(true),
		m_node(nullptr)
	{

	}

	void Component::set_node(Node* node)
	{
		if (m_node)
		{
			//m_node->removeComponent(std::make_shared<Component>(this));
		}
		if (node)
		{

		}
		m_node = node;
	}
}