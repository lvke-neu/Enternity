#include "Scene3D.h"
#include "Node3D.h"

namespace Enternity
{
	Scene3D::Scene3D()
	{
		m_rootNode = new Node3D;
		m_rootNode->set_name("RootNode");


		for (int i = 0; i < 5; i++)
		{
			Node3D* node = new Node3D;
			node->set_name(std::to_string(i));
			node->addToParent(m_rootNode);

			for (int j = 0; j < 5; j++)
			{
				Node3D* node2 = new Node3D;
				node2->set_name(std::to_string(i) + "_" + std::to_string(j));
				node2->addToParent(node);
			}
		}
	}

	Scene3D::~Scene3D()
	{
		SAFE_DELETE_SET_NULL(m_rootNode);
	}
}