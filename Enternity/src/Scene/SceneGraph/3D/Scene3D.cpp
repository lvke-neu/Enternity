#include "Scene3D.h"
#include "Node3D.h"
#include "Camera3DComponent.h"
#include "CameraController.h"

namespace Enternity
{
	Scene3D::Scene3D()
	{
		m_rootNode = new Node;
		m_rootNode->set_name("RootNode");

		initCamera();
	}

	Scene3D::~Scene3D()
	{
		SAFE_DELETE_SET_NULL(m_rootNode);
	}

	void Scene3D::initCamera()
	{
		Node3D* cameraNode = new Node3D;
		cameraNode->set_name("CameraNode");
		cameraNode->addToParent(m_rootNode);

		Camera3DComponent* camera3DComponent = new Camera3DComponent;
		camera3DComponent->addToNode(cameraNode);

		CameraController* cameraController = new CameraController;
		cameraController->addToNode(cameraNode);
	}
}