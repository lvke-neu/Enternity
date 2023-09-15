#include "Scene3D.h"
#include "Node3D.h"
#include "Camera3DComponent.h"

namespace Enternity
{
	Scene3D::Scene3D()
	{
		m_rootNode = new Node3D;
		m_rootNode->set_name("RootNode");
	}

	Scene3D::~Scene3D()
	{
		SAFE_DELETE_SET_NULL(m_rootNode);
	}
}