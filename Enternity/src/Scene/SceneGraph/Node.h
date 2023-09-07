#pragma once
#include "Common/Macro.h"
#include <string>
#include <set>
#include <memory>

namespace Enternity
{
	class Node
	{
	public:
		Node();
		virtual ~Node();
	public:
		GET(std::string, uuid);
		GET_SET(std::string, name);
		GET(std::set<Node*>, childs);

		void addToParent(Node* node);
		void removeFromParent();
	private:
		std::string m_uuid;
		std::string m_name;

		Node* m_parent;
		std::set<Node*> m_childs;
	};
}
