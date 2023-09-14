#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class Node;
	class Scene
	{
	public:
		Scene() = default;
		virtual ~Scene() = default;
	public:
		GET_SET(Node*, rootNode);
	protected:
		Node* m_rootNode;
	};
}