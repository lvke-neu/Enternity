#include "Scene3D.h"
#include "Node3D.h"
#include "SceneGraph/Component.h"

namespace Enternity
{
	Scene3D::Scene3D()
	{
		m_rootNode = new Node3D;
		m_rootNode->set_name("RootNode");

		/*	Component* comp = new Component;
			comp->set_name("Comp_RootNode");
			comp->addToNode(m_rootNode);*/

		for (int i = 0; i < 5; i++)
		{
			Node3D* node = new Node3D;
			node->set_name(std::to_string(i));
			node->addToParent(m_rootNode);

			/*	Component* comp2 = new Component;
				comp2->set_name("Comp_" + std::to_string(i));
				comp2->addToNode(node);*/

			for (int j = 0; j < 5; j++)
			{
				Node3D* node2 = new Node3D;
				node2->set_name(std::to_string(i) + "_" + std::to_string(j));
				node2->addToParent(node);

				/*Component* comp3 = new Component;
				comp3->set_name("Comp_" + std::to_string(i) + "_" + std::to_string(j));
				comp3->addToNode(node2);*/
			}
		}
	}

	Scene3D::~Scene3D()
	{
		SAFE_DELETE_SET_NULL(m_rootNode);
	}
}