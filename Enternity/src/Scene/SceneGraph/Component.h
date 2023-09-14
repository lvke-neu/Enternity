#pragma once
#include "Common/Macro.h"
#include <string>

namespace Enternity
{
	class Node;
	class Component
	{
	public:
		Component();
		virtual ~Component();
	public:
		GET(Node*, node);
		GET_SET(std::string, name);
		void addToNode(Node* node);
		void removeFromNode();
	protected:
		Node* m_node;
		std::string m_name;
	};
}

