#pragma once
#include "Engine/Reference.h"

namespace Enternity
{
	class Node;
	class Component : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		Component();
		virtual ~Component();
	public:
		GET_CLASS_NAME(Component);
	public:
		GET(std::string, uuid);
		GET_SET(bool, enable);
		GET(Node*, node);
	public:
		void addToNode(Node* node);
		void removeFromNode();
	protected:
		bool m_enable;
		Node* m_node;
	};
}

