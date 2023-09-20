#include "Scene3D.h"
#include "Node3D.h"
#include "Camera3DComponent.h"
#include "CameraController.h"
#include "Visual3DComponent.h"
#include "SkyBoxComponent.h"
#include "TerrainComponent.h"
#include "Model3DComponent.h"
#include "Engine/Engine.h"
#include "Engine/Command.h"
#include "Engine/AssetLoader.h"
#include "Graphics/Material.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/GraphicsSystem.h"

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

	void Scene3D::tick()
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
		baseSceneNode->getTransform().set_translation({ 0.0f, -2.0f, 0.0f });
		baseSceneNode->getTransform().set_scale({ 10.0f, 10.0f, 10.0f });

		SkyBoxComponent* skyBoxComponent = new SkyBoxComponent;
		skyBoxComponent->addToNode(baseSceneNode);

		//TerrainComponent* terrainComponent = new TerrainComponent;
		//terrainComponent->addToNode(baseSceneNode);
	}

	void Scene3D::initObjcet()
	{
		//Node3D* sceneObjectNode1 = new Node3D;
		//sceneObjectNode1->set_name("SceneObjectNode1");
		//sceneObjectNode1->addToParent(m_rootNode);
		//sceneObjectNode1->getTransform().set_translation({ -2.0f, 0.0f, 0.0f });

		//Visual3DComponent* visual3DComponent1 = new Visual3DComponent;
		//visual3DComponent1->addToNode(sceneObjectNode1);
		//

		//Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube",
		//	[=](Asset* asset)
		//	{
		//		visual3DComponent1->set_mesh((Mesh*)asset);
		//	});

		//Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/visual3d/visual3d.rdr",
		//	[=](Asset* asset)
		//	{
		//		visual3DComponent1->set_renderer((Renderer*)asset);
		//	});

		//Material* material = new Material;
		//material->set_ambientColor(Color::s_black);
		//material->set_ambientTexturePath("texture://TEXTURE_2D?assets/textures/box_diffuse.png");
		//material->set_diffuseTexturePath("texture://TEXTURE_2D?assets/textures/box_diffuse.png");
		//material->set_specularTexturePath("texture://TEXTURE_2D?assets/textures/box_specular.png");
		//material->load();
		//visual3DComponent1->set_material(material);
		
		Node3D* modelNode = new Node3D;
		modelNode->set_name("ModelNode");
		modelNode->addToParent(m_rootNode);

		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/2nrtbod1out/2nrtbod1out.obj",
		[=](Asset* asset)
		{
			Model3DComponent* model3DComponent = new Model3DComponent((Model*)asset);
			model3DComponent->addToNode(modelNode);
		});
	}
}