#include "Component.h"
#include "Node.h"
#include "Common/Utility.h"

namespace Enternity
{
	Component::Component() : m_enable(true), m_node(nullptr)
	{
		m_uuid = Utility::GenerateUUID();
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
	
	RTTR_REGISTRATION
	{
		rttr::registration::class_<Component>("Component")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("enable",&Component::get_enable, &Component::set_enable);
	}
}