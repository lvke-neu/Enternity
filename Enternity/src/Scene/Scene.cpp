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
#include "ECS/ModelComponent.h"
#include "ECS/PBRMaterialComponent.h"
#include "ECS/PointLightComponent.h"
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

		auto entity1 = createEntity();
		entity1.getComponent<NameComponent>().name = "sphere.fbx1";
		entity1.addComponent<TransformComponent>().translation = { -5.0f, 0.0f, 0.0f };
		entity1.addComponent<ModelComponent>();
		entity1.addComponent<PBRMaterialComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/basic/Sphere.fbx",
			[=](Asset* asset)
			{
				entity1.getComponent<ModelComponent>().model = dynamic_cast<Model*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/pbr.rdr",
			[=](Asset* asset)
			{
				entity1.getComponent<ModelComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/albedo.png",
			[=](Asset* asset)
			{
				entity1.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/normal.png",
			[=](Asset* asset)
			{
				entity1.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});		
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/metallic.png",
			[=](Asset* asset)
			{
				entity1.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/roughness.png",
			[=](Asset* asset)
			{
				entity1.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/ao.png",
			[=](Asset* asset)
			{
				entity1.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
			});

		auto entity2 = createEntity();
		entity2.getComponent<NameComponent>().name = "sphere.fbx1";
		entity2.addComponent<TransformComponent>().translation = {5.0f, 0.0f, 0.0f };
		entity2.addComponent<ModelComponent>();
		entity2.addComponent<PBRMaterialComponent>();
		Engine::GetInstance().getAssetLoader()->getAsset("model://assets/models/basic/Sphere.fbx",
			[=](Asset* asset)
			{
				entity2.getComponent<ModelComponent>().model = dynamic_cast<Model*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/pbr/pbr.rdr",
			[=](Asset* asset)
			{
				entity2.getComponent<ModelComponent>().renderer = dynamic_cast<Renderer*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/albedo.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().albedo = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/normal.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().normal = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/metallic.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().metallic = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/roughness.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().roughness = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D&Slip=false?assets/textures/pbr/rusted_iron/ao.png",
			[=](Asset* asset)
			{
				entity2.getComponent<PBRMaterialComponent>().ao = dynamic_cast<Texture2D*>(asset);
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

			if (it->second.hasComponent<ModelComponent>())
			{
				it->second.getComponent<ModelComponent>().unload();
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

			if (it->second.hasComponent<ModelComponent>())
			{
				it->second.getComponent<ModelComponent>().unload();
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
		comp.translation = glm::vec3(0.0f, 0.0f, 10.0f);
		//comp.rotation = glm::vec3(-6.20, -11.00, 0);
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
		m_scenePointLight = createEntity();
		m_scenePointLight.getComponent<NameComponent>().name = "PointLight";
		auto& pointLightComponent = m_scenePointLight.addComponent<PointLightComponent>();
		pointLightComponent.position = { 0.0f };
		pointLightComponent.color = glm::vec3(300.f);
	}
}