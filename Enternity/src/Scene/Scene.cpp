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
#include "ECS/PBRMaterialComponent.h"
#include "ECS/SunLightComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Scene/Model/Model.h"
#include "Common/Macro.h"

namespace Enternity
{
	static Entity s_Entity;
	Scene::Scene()
	{
		initPostProcess();
		initCamera();
		initSkyBox();
		initLight();

		auto entity = createEntity();
		entity.getComponent<NameComponent>().name = "plane";
		entity.addComponent<TransformComponent>(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(100.0f));
		entity.addComponent<StaticModelComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/basic/Plane.fbx",
			[=](Asset* asset)
			{
				entity.getComponent<StaticModelComponent>().model = dynamic_cast<Model*>(asset);
			});
		entity.addComponent<PBRMaterialComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/staticModelpbr.rdr",
			[=](Asset* asset)
			{
				entity.getComponent<PBRMaterialComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/albedo.png",
			[=](Asset* asset)
			{
				entity.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/normal.png",
			[=](Asset* asset)
			{
				entity.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/metallic.png",
			[=](Asset* asset)
			{
				entity.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/roughness.png",
			[=](Asset* asset)
			{
				entity.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/ao.png",
			[=](Asset* asset)
			{
				entity.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
			});


		auto entity2 = createEntity();
		entity2.getComponent<NameComponent>().name = "static model";
		entity2.addComponent<TransformComponent>(glm::vec3(0.0f, 0.0f, -30.0f), glm::vec3(0.0f), glm::vec3(0.05f));
		entity2.addComponent<StaticModelComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/house/house.obj",
			[=](Asset* asset)
			{
				entity2.getComponent<StaticModelComponent>().model = dynamic_cast<Model*>(asset);
			});
		entity2.addComponent<PBRMaterialComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/staticModelpbr.rdr",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/models/house/house.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/normal.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/metallic.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/roughness.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/ao.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
			});

	
		auto entity3 = createEntity();
		s_Entity = entity3;
		entity3.getComponent<NameComponent>().name = "walk skeleton model";
		entity3.addComponent<TransformComponent>(glm::vec3(-14.00f, 1.13f, -2.16f), glm::vec3(0.0f), glm::vec3(10.0f));
		entity3.addComponent<SkeletonModelComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/walk/Standard Walk.dae",
			[=](Asset* asset)
			{
				entity3.getComponent<SkeletonModelComponent>().model = dynamic_cast<Model*>(asset);
			});
		entity3.addComponent<PBRMaterialComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/skeletonModelpbr.rdr",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/models/animation/walk/textures/Ch33_1001_Diffuse.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/normal.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/metallic.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/roughness.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/ao.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
			});



		auto entity4 = createEntity();
		entity4.getComponent<NameComponent>().name = "run skeleton model";
		entity4.addComponent<TransformComponent>(glm::vec3(14.00f, 1.13f, -2.16f), glm::vec3(0.0f), glm::vec3(10.0f));
		entity4.addComponent<SkeletonModelComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/Ymca Dance/Ymca Dance.dae",
			[=](Asset* asset)
			{
				entity4.getComponent<SkeletonModelComponent>().model = dynamic_cast<Model*>(asset);
			});

		auto& modelcomp = entity4.getComponent<SkeletonModelComponent>();

		entity4.addComponent<PBRMaterialComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/skeletonModelpbr.rdr",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/models/animation/Ymca Dance/textures/Ch06_1001_Diffuse.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/normal.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/metallic.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/roughness.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/default/ao.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
			});
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

			m_registry.destroy(it->first);
			it = m_entities.erase(it);
		}
	}

	void Scene::tick(float deltaTime)
	{
		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::Up))
		{
			s_Entity.getComponent<TransformComponent>().moveZAxis(10 * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::Down))
		{
			s_Entity.getComponent<TransformComponent>().moveZAxis(-10 * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::Left))
		{
			s_Entity.getComponent<TransformComponent>().rotateAlongYAxis(-100 * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::Right))
		{
			s_Entity.getComponent<TransformComponent>().rotateAlongYAxis(100 * deltaTime);
		}
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