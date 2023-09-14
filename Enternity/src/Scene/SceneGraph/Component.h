#pragma once
#include "Common/Macro.h"
#include <string>
#include <rttr/registration>

namespace Enternity
{
	class Node;
	class Component
	{
		RTTR_ENABLE();
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
		std::string m_uuid;
		bool m_enable;
		Node* m_node;
	};
}

