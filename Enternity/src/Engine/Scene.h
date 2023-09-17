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
		GET(Node*, rootNode);
	protected:
		Node* m_rootNode;
	};
}