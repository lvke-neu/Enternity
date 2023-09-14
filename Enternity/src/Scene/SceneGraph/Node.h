#pragma once
#include "Common/Macro.h"
#include <vector>
#include <string>

namespace Enternity
{
	class Component;
	class Node
	{
	public:
		Node();
		virtual ~Node();
	public:
		GET(std::string, uuid);
		GET_SET(std::string, name);
		GET(std::vector<Node*>, childs);
		GET(std::vector<Component*>, components);
	public:
		void addToParent(Node* parent);
		void removeFromParent();

		void addComponent(Component* component);
		void removeComponent(Component* component);
	private:
		std::string m_uuid;
		std::string m_name;
		Node* m_parent;
		std::vector<Node*> m_childs;
		std::vector<Component*> m_components;
	};
}
