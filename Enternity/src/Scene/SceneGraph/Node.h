#pragma once
#include "Engine/Reference.h"

namespace Enternity
{
	class Component;
	class Node : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		Node();
		virtual ~Node();
	public:
		GET_CLASS_NAME(Node);
	public:
		GET_SET(std::string, name);
		GET(std::vector<Node*>, childs);
		GET(std::vector<Component*>, components);
	public:
		void addToParent(Node* parent);
		void removeFromParent();

		void addComponent(Component* component);
		void removeComponent(Component* component);
	private:
		std::string m_name;
		Node* m_parent;
		std::vector<Node*> m_childs;
		std::vector<Component*> m_components;
	};
}
