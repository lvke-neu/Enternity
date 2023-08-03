#include "Scene.h"
#include "CameraController.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
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
	Scene::Scene()
	{
		initPostProcess();
		initCamera();
		initSkyBox();
		initLight();

		//glm::vec3 trans[6] = 
		//{ 
		//	{5.0f, 0.0f, 0.0f},{-5.0f, 0.0f, 0.0f},
		//	{0.0f, 5.0f, 0.0f},{0.0f, -5.0f, 0.0f},
		//	{0.0f, 0.0f, 5.0f},{0.0f, 0.0f, -5.0f}
		//};

		//std::string path[6] = { {"default"},{"default"},{"plastic"},{"wall"},{"rusted_iron"},{"rusted_iron"} };

		//for (int i = 0; i < 6; i++)
		//{
		//	auto entity = createEntity();
		//	entity.getComponent<NameComponent>().name = "sphere.fbx1";
		//	entity.addComponent<TransformComponent>().translation = trans[i];
		//	entity.addComponent<ModelComponent>();
		//	entity.addComponent<PBRMaterialComponent>();
		//	Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/basic/Sphere.fbx",
		//		[=](Asset* asset)
		//		{
		//			entity.getComponent<ModelComponent>().model = dynamic_cast<Model*>(asset);
		//		});
		//	Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/pbr.rdr",
		//		[=](Asset* asset)
		//		{
		//			entity.getComponent<ModelComponent>().renderer = dynamic_cast<Renderer*>(asset);
		//		});
		//	Engine::GetInstance().getAssetLoader()->getAsset(("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/" + path[i] +"/albedo.png").c_str(),
		//		[=](Asset* asset)
		//		{
		//			entity.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
		//		});
		//	Engine::GetInstance().getAssetLoader()->getAsset(("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/" + path[i] + "/normal.png").c_str(),
		//		[=](Asset* asset)
		//		{
		//			entity.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
		//		});
		//	Engine::GetInstance().getAssetLoader()->getAsset(("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/" + path[i] + "/metallic.png").c_str(),
		//		[=](Asset* asset)
		//		{
		//			entity.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
		//		});
		//	Engine::GetInstance().getAssetLoader()->getAsset(("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/" + path[i] + "/roughness.png").c_str(),
		//		[=](Asset* asset)
		//		{
		//			entity.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
		//		});
		//	Engine::GetInstance().getAssetLoader()->getAsset(("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/" + path[i] + "/ao.png").c_str(),
		//		[=](Asset* asset)
		//		{
		//			entity.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
		//		});
		//}

		auto entity = createEntity();
		entity.getComponent<NameComponent>().name = "plane";
		auto& trans = entity.addComponent<TransformComponent>();
		trans.scale = { 100.0f };
		//trans.translation = { 0.0f, -10.0f, 0.0f };
		
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
		entity2.addComponent<TransformComponent>().scale = { 5.0f };
		entity2.addComponent<StaticModelComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/silly_dancing.fbx",
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
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/albedo.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/normal.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/metallic.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/roughness.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/ao.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
			});


		auto entity3 = createEntity();
		entity3.getComponent<NameComponent>().name = "skeleton model";
		auto& trans3 = entity3.addComponent<TransformComponent>();
		trans3.scale = { 7.0f };
		trans3.translation = { -14.00, 1.13, -2.16 };
		entity3.addComponent<SkeletonModelComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/vampire/dancing_vampire.dae",
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
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/models/animation/vampire/textures/Vampire_diffuse.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/normal.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/metallic.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/roughness.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/ao.png",
			[=](Asset* asset)
			{
				entity3.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
			});



		auto entity4 = createEntity();
		entity4.getComponent<NameComponent>().name = "skeleton model2";
		auto& trans4 = entity4.addComponent<TransformComponent>();
		trans4.scale = { 5.0f };
		trans4.translation = { 14.00, 1.13, -2.16 };
		entity4.addComponent<SkeletonModelComponent>().model = dynamic_cast<Model*>(Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/animation/silly_dancing.fbx"));

		auto& modelcomp = entity4.getComponent<SkeletonModelComponent>();

		entity4.addComponent<PBRMaterialComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/skeletonModelpbr.rdr",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/box_diffuse.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/normal.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/metallic.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/roughness.png",
			[=](Asset* asset)
			{
				entity4.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/pbr/rusted_iron/ao.png",
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
		auto& comp = m_sceneCamera.addComponent<TransformComponent>();
		comp.translation = glm::vec3(-24.75, 19.59, 18.22);
		comp.rotation = glm::vec3(-16.00, -65.90, 0);
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