#include "Scene.h"
#include "Engine.h"
#include "Node.h"
#include "Component.h"
#include "Graphics/GraphicsSystem.h"

namespace Enternity
{
	void Scene::tick()
	{
		TreeNode(m_rootNode,
			[](Node* node)
			{
				for (const auto& comp : node->get_components())
				{
					if (comp)
					{
						Engine::GetInstance().getGraphicsSystem()->addCommand(comp->get_command());
					}
				}
			});
	}

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