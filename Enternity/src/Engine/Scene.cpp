#include "Scene.h"
#include "Node.h"

namespace Enternity
{
	void Scene::TreeNode(Node* node, std::function<void(Node* node)> callback)
	{
		if (!node)
		{
			return;
		}

		callback(node);
		for (const auto& child : node->get_childs())
		{
			TreeNode(child, callback);
		}
	}
}