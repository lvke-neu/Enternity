#include "Scene.h"
#include "CameraController.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Engine/EventSystem.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/NameComponent.h"
#include "ECS/PostProcessComponent.h"
#include "ECS/SkyBoxComponent.h"
#include "ECS/Visual3DComponent.h"
#include "ECS/SkeletonModelComponent.h"
#include "ECS/StaticModelComponent.h"
#include "ECS/ModelComponent.h"
#include "ECS/PBRMaterialComponent.h"
#include "ECS/SunLightComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Scene/Model/Model.h"
#include "Common/Macro.h"
#include "SceneGraph/Node3D.h"

namespace Enternity
{
	Scene::Scene()
	{
		initPostProcess();
		initCamera();
		initSkyBox();
		initLight();

		m_rootNode = new Node3D;
		m_rootNode->setName("RootNode");

		for (int i = 0; i < 5; i++)
		{
			Node3D* node = new Node3D;
			node->setName(std::to_string(i).c_str());
			node->addToParent(m_rootNode);

			for (int j = 0; j < 5; j++)
			{
				Node3D* node2 = new Node3D;
				node2->setName(std::to_string(i)+ "_" + std::to_string(j));
				node2->addToParent(node);
			}
		}



		//auto entity = createEntity();
		//entity.getComponent<NameComponent>().name = "plane";
		//entity.addComponent<TransformComponent>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(100.0f));
		//entity.addComponent<ModelComponent>();
		//Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/basic/Plane.fbx",
		//	[=](Asset* asset)
		//	{
		//		entity.getComponent<ModelComponent>().model = dynamic_cast<Model*>(asset);
		//		entity.getComponent<ModelComponent>().model->setUseTexture(false);
		//	});
		//Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/model/model.rdr",
		//	[=](Asset* asset)
		//	{
		//		entity.getComponent<ModelComponent>().renderer = dynamic_cast<Renderer*>(asset);
		//	});

		//auto entity1 = createEntity();
		//entity1.getComponent<NameComponent>().name = "test model1";
		//entity1.addComponent<TransformComponent>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		//entity1.addComponent<ModelComponent>();
		//Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/walk/Standard Walk.dae",
		//	[=](Asset* asset)
		//	{
		//		entity1.getComponent<ModelComponent>().model = dynamic_cast<Model*>(asset);
		//	});
		//Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/model/model.rdr",
		//	[=](Asset* asset)
		//	{
		//		entity1.getComponent<ModelComponent>().renderer = dynamic_cast<Renderer*>(asset);
		//	});
		//
		//auto entity2 = createEntity();
		//entity2.getComponent<NameComponent>().name = "test model2";
		//entity2.addComponent<TransformComponent>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f));
		//entity2.addComponent<ModelComponent>();
		//Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/Ymca Dance/Ymca Dance.dae",
		//	[=](Asset* asset)
		//	{
		//		entity2.getComponent<ModelComponent>().model = dynamic_cast<Model*>(asset);
		//	});
		//Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/model/model.rdr",
		//	[=](Asset* asset)
		//	{
		//		entity2.getComponent<ModelComponent>().renderer = dynamic_cast<Renderer*>(asset);
		//	});
	}

	Scene::~Scene()
	{
		deleteAllEntity();

		SAFE_DELETE_SET_NULL(m_cameraController);
	}

	Entity Scene::createEntity()
	{
		Entity entity(&m_registry);
		m_entities.insert({ entity.getEnttID(), entity });

		return entity;
	}

	Entity Scene::getEntity(entt::entity id)
	{
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			return m_entities[id];
		}

		return Entity();
	}

	void Scene::deleteEntityById(entt::entity id)
	{
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			if (it->second.hasComponent<PostProcessComponent>())
			{
				it->second.getComponent<PostProcessComponent>().unload();
			}

			if (it->second.hasComponent<SkyBoxComponent>())
			{
				it->second.getComponent<SkyBoxComponent>().unload();
			}

			if (it->second.hasComponent<Visual3DComponent>())
			{
				it->second.getComponent<Visual3DComponent>().unload();
			}

			if (it->second.hasComponent<SkeletonModelComponent>())
			{
				it->second.getComponent<SkeletonModelComponent>().unload();
			}			
			
			if (it->second.hasComponent<StaticModelComponent>())
			{
				it->second.getComponent<StaticModelComponent>().unload();
			}

			if (it->second.hasComponent<PBRMaterialComponent>())
			{
				it->second.getComponent<PBRMaterialComponent>().unload();
			}

			if (it->second.hasComponent<ModelComponent>())
			{
				it->second.getComponent<ModelComponent>().unload();
			}

			m_registry.destroy(it->first);
			m_entities.erase(id);
		}
	}

	void Scene::deleteAllEntity()
	{
		for (auto it = m_entities.begin(); it != m_entities.end();)
		{
			if (it->second.hasComponent<PostProcessComponent>())
			{
				it->second.getComponent<PostProcessComponent>().unload();
			}

			if (it->second.hasComponent<SkyBoxComponent>())
			{
				it->second.getComponent<SkyBoxComponent>().unload();
			}

			if (it->second.hasComponent<Visual3DComponent>())
			{
				it->second.getComponent<Visual3DComponent>().unload();
			}

			if (it->second.hasComponent<SkeletonModelComponent>())
			{
				it->second.getComponent<SkeletonModelComponent>().unload();
			}

			if (it->second.hasComponent<StaticModelComponent>())
			{
				it->second.getComponent<StaticModelComponent>().unload();
			}

			if (it->second.hasComponent<PBRMaterialComponent>())
			{
				it->second.getComponent<PBRMaterialComponent>().unload();
			}
			
			if (it->second.hasComponent<ModelComponent>())
			{
				it->second.getComponent<ModelComponent>().unload();
			}

			m_registry.destroy(it->first);
			it = m_entities.erase(it);
		}
	}

	void Scene::tick(float deltaTime)
	{
		
	}

	void Scene::initPostProcess()
	{
		m_scenePostprocess = createEntity();
		m_scenePostprocess.getComponent<NameComponent>().name = "PostProcess";
		m_scenePostprocess.addComponent<PostProcessComponent>();

		Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=plane",
			[&](Asset* asset)
			{
				m_scenePostprocess.getComponent<PostProcessComponent>().mesh= dynamic_cast<Mesh*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/postprocess/postprocess.rdr",
			[&](Asset* asset)
			{
				m_scenePostprocess.getComponent<PostProcessComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
	}

	void Scene::initCamera()
	{
		m_sceneCamera = createEntity();
		m_sceneCamera.getComponent<NameComponent>().name = "Camera";
		m_sceneCamera.addComponent<TransformComponent>(glm::vec3(-24.75, 19.59, 18.22), glm::vec3(-16.00, -65.90, 0), glm::vec3(1.0f));
		m_sceneCamera.addComponent<CameraComponent>().moveSpeed = 30;
		m_cameraController = new CameraController(&m_sceneCamera);
	}

	void Scene::initSkyBox()
	{
		m_sceneSkybox = createEntity();
		m_sceneSkybox.getComponent<NameComponent>().name = "SkyBox";
		m_sceneSkybox.addComponent<SkyBoxComponent>();

		Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube",
			[&](Asset* asset)
			{
				m_sceneSkybox.getComponent<SkyBoxComponent>().mesh = dynamic_cast<Mesh*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/skybox/skybox.rdr",
			[&](Asset* asset)
			{
				m_sceneSkybox.getComponent<SkyBoxComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://CUBE_MAP_HDR?assets/textures/hdr/evening_meadow_4k.hdr",
			[&](Asset* asset)
			{
				m_sceneSkybox.getComponent<SkyBoxComponent>().textureCubeMapHDR = dynamic_cast<TextureCubeMapHDR*>(asset);
			});
	}

	void Scene::initLight()
	{
		m_sceneSunlight = createEntity();
		m_sceneSunlight.getComponent<NameComponent>().name = "Sunlight";
		auto& sunLightComponent = m_sceneSunlight.addComponent<SunLightComponent>();
		sunLightComponent.color = { 5.0f };
		sunLightComponent.direction = {0.0f, -20.0f, -20.0f };
		//m_sceneSunlight.addComponent<TransformComponent>().scale = { 0.2f };
		//m_sceneSunlight.addComponent<Visual3DComponent>();

		//Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube",
		//	[&](Asset* asset)
		//	{
		//		m_sceneSunlight.getComponent<Visual3DComponent>().mesh = dynamic_cast<Mesh*>(asset);
		//	});
		//Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/light/lightgzmo.rdr",
		//	[&](Asset* asset)
		//	{
		//		m_sceneSunlight.getComponent<Visual3DComponent>().renderer = dynamic_cast<Renderer*>(asset);
		//	});
	}
}