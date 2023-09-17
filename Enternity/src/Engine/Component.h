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
		GET_SET(bool, enable);
		GET(Node*, node);
	public:
		virtual void tick() {};
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
	};
}

