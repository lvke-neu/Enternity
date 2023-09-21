#include "Scene3D.h"
#include "Node3D.h"
#include "Camera3DComponent.h"
#include "CameraController.h"
#include "Visual3DComponent.h"
#include "SkyBoxComponent.h"
#include "TerrainComponent.h"
#include "Model3DComponent.h"
#include "Visual3D.h"
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
		
		Node3D* modelNode1 = new Node3D;
		modelNode1->set_name("ModelNode1");
		modelNode1->addToParent(m_rootNode);
		modelNode1->getTransform().set_scale({ 0.1f ,.1f ,.1f});
		modelNode1->getTransform().set_translation({ 0.1f ,-5.0f ,.1f});
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/walk/Standard Walk.dae",
		[=](Asset* asset)
		{
			Model3DComponent* model3DComponent = new Model3DComponent((Model*)asset);
			model3DComponent->addToNode(modelNode1);
			//not delete this asset, visual3d shared_ptr manager it
		});


		Node3D* modelNode2 = new Node3D;
		modelNode2->set_name("ModelNode2");
		modelNode2->addToParent(m_rootNode);
		modelNode2->getTransform().set_scale({ 0.1f ,.1f ,.1f });
		modelNode2->getTransform().set_translation({ 16.1f ,-5.0f ,.1f });
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/Ymca Dance/Ymca Dance.dae",
			[=](Asset* asset)
			{
				Model3DComponent* model3DComponent = new Model3DComponent((Model*)asset);
				model3DComponent->addToNode(modelNode2);
				//not delete this asset, visual3d shared_ptr manager it
			});
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/2nrtbod1out/2nrtbod1out.obj",
			[=](Asset* asset)
			{
				Model3DComponent* model3DComponent = new Model3DComponent((Model*)asset);
				model3DComponent->addToNode(modelNode2);
				//not delete this asset, visual3d shared_ptr manager it
			});

		Node3D* visual3DNode = new Node3D;
		visual3DNode->set_name("Visual3DNode");
		visual3DNode->addToParent(m_rootNode);
		
		Visual3D* visual3D = new Visual3D;
		Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube",
		[=](Asset* asset)
		{
			visual3D->set_mesh(std::shared_ptr<Mesh>((Mesh*)asset));
		});

		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/visual3d/visual3d.rdr",
		[=](Asset* asset)
		{
			visual3D->set_renderer(std::shared_ptr<Renderer>((Renderer*)asset));
		});
		Material* material = new Material;
		material->set_ambientColor(Color::s_black);
		material->set_diffuseTexturePath("texture://TEXTURE_2D?assets/textures/box_diffuse.png");
		material->load();
		visual3D->set_material(std::shared_ptr<Material>(material));

		Visual3DComponent* visual3DComponent = new Visual3DComponent(visual3D);

		visual3DComponent->addToNode(visual3DNode);
	}
}