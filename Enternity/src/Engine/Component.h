#pragma once
#include "Engine/Reference.h"

namespace Enternity
{
	class Node;
	class Command;
	class Component : public Reference
	{
		RTTR_ENABLE(Reference);
	public:
		Component();
		virtual ~Component();
	public:
		GET_CLASS_NAME(Component);
	public:
		GET_SET(bool, enable);
		GET(Node*, node);
		GET(Command*, command);
	public:
		virtual void command() {};
		void addToNode(Node* node);
		void removeFromNode();

		template<typename T>
		T* getNode()
		{
			return (T*)m_node;
		}
	protected:
		bool m_enable;
		Node* m_node;
		Command* m_command;
	};
}

