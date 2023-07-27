#include "Scene.h"
#include "CameraController.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/NameComponent.h"
#include "ECS/PostProcessComponent.h"
#include "ECS/SkyBoxComponent.h"
#include "ECS/Visual3DComponent.h"
#include "ECS/ModelComponent.h"
#include "ECS/PBRMaterialComponent.h"
#include "ECS/PointLightComponent.h"
#include "Engine/Engine.h"
#include "Common/Macro.h"

namespace Enternity
{
	Scene::Scene()
	{
		//scene postprocess
		m_scenePostprocess = createEntity();
		m_scenePostprocess.getComponent<NameComponent>().name = "PostProcess";
		m_scenePostprocess.addComponent<PostProcessComponent>().load();

		//scene camera
		m_sceneCamera = createEntity();
		m_sceneCamera.getComponent<NameComponent>().name = "Camera";
		auto& comp = m_sceneCamera.addComponent<TransformComponent>();
		comp.translation = glm::vec3(0.0f, 0.0f, 10.0f);
		//comp.rotation = glm::vec3(-6.20, -11.00, 0);
		m_sceneCamera.addComponent<CameraComponent>().moveSpeed = 30;
		m_cameraController = new CameraController(&m_sceneCamera);

		//scene skybox
		m_sceneSkybox = createEntity();
		m_sceneSkybox.getComponent<NameComponent>().name = "SkyBox";
		m_sceneSkybox.addComponent<SkyBoxComponent>().load("texture://CUBE_MAP_HDR?assets/textures/hdr/evening_meadow_4k.hdr");

		//scene light
		m_scenePointLight = createEntity();
		m_scenePointLight.getComponent<NameComponent>().name = "PointLight";
		auto& pointLightComponent = m_scenePointLight.addComponent<PointLightComponent>();
		pointLightComponent.position = glm::vec3(10.0f, 10.0f, 10.0f);
		pointLightComponent.color = glm::vec3(300.f);

		//auto entity1 = createEntity();
		//entity1.getComponent<NameComponent>().name = "cube";
		//entity1.addComponent<Visual3DComponent>().load("mesh://primitive=cube", "renderer://assets/shaders/visual3d/visual3d.rdr", "texture://TEXTURE_2D?assets/textures/box_diffuse.png");
		//entity1.addComponent<TransformComponent>();

		auto entity1 = createEntity();
		entity1.getComponent<NameComponent>().name = "sphere.fbx";
		entity1.addComponent<ModelComponent>().load("model://assets/models/basic/Sphere.fbx", "renderer://assets/shaders/pbr/pbr.rdr");
		entity1.addComponent<TransformComponent>();
		auto& pbrMaterialComponent = entity1.addComponent<PBRMaterialComponent>();
		pbrMaterialComponent.albedo = glm::vec3(1.0f, 0.0f, 0.0f);
		pbrMaterialComponent.metallic = 0.14f;
		pbrMaterialComponent.roughness = 0.08f;
		pbrMaterialComponent.ao = 1.0f;
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

			m_registry.destroy(it->first);
			it = m_entities.erase(it);
		}
	}

	void Scene::tick(float deltaTime)
	{

	}
}