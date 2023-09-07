#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class Node;
	class Component
	{
	public:
		Component();
	public:
		GET_SET(bool, enable);
		GET(Node*, node);

		void set_node(Node* node);
	private:
		bool m_enable;
		Node* m_node;
	};
}

