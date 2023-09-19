#pragma once
#include "Common/Macro.h"
#include <functional>

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

		virtual void tick() {};
	public:
		static void TreeNode(Node* node, std::function<void (Node* node)> callback);
	protected:
		Node* m_rootNode;
	};
}