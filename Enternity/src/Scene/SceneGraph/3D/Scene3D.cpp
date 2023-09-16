#include "Scene3D.h"
#include "Node3D.h"
#include "Camera3DComponent.h"
#include "CameraController.h"
#include "Visual3DComponent.h"
#include "SkyBoxComponent.h"

namespace Enternity
{
	Scene3D::Scene3D()
	{
		m_rootNode = new Node;
		m_rootNode->set_name("RootNode");

		initCamera();
		initBaseScene();
		initObjcet();
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
		cameraNode->getTransform().set_translation({ 0.0f, 0.0f, 5.0f });

		Camera3DComponent* camera3DComponent = new Camera3DComponent;
		camera3DComponent->addToNode(cameraNode);

		CameraController* cameraController = new CameraController;
		cameraController->addToNode(cameraNode);
	}

	void Scene3D::initBaseScene()
	{
		Node3D* baseSceneNode = new Node3D;
		baseSceneNode->set_name("BaseSceneNode");
		baseSceneNode->addToParent(m_rootNode);

		SkyBoxComponent* skyBoxComponent = new SkyBoxComponent;
		skyBoxComponent->addToNode(baseSceneNode);
	}

	void Scene3D::initObjcet()
	{
		Node3D* sceneObjectNode1 = new Node3D;
		sceneObjectNode1->set_name("SceneObjectNode1");
		sceneObjectNode1->addToParent(m_rootNode);
		sceneObjectNode1->getTransform().set_translation({ -2.0f, 0.0f, 0.0f });

		Visual3DComponent* visual3DComponent1 = new Visual3DComponent;
		visual3DComponent1->addToNode(sceneObjectNode1);

		Node3D* sceneObjectNode2 = new Node3D;
		sceneObjectNode2->set_name("SceneObjectNode2");
		sceneObjectNode2->addToParent(m_rootNode);
		sceneObjectNode2->getTransform().set_translation({ 2.0f, 0.0f, 0.0f });

		Visual3DComponent* visual3DComponent2 = new Visual3DComponent;
		visual3DComponent2->addToNode(sceneObjectNode2);
	}
}