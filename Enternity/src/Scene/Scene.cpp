#include "Scene.h"
#include "CameraController.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/NameComponent.h"
#include "ECS/PostProcessComponent.h"
#include "ECS/SkyBoxComponent.h"
#include "ECS/Visual3DComponent.h"
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
		comp.translation = glm::vec3(0.28, 8.41, 19.70);
		comp.rotation = glm::vec3(-6.20, -11.00, 0);
		m_sceneCamera.addComponent<CameraComponent>().moveSpeed = 30;
		m_cameraController = new CameraController(&m_sceneCamera);

		//scene skybox
		m_sceneSkybox = createEntity();
		m_sceneSkybox.getComponent<NameComponent>().name = "SkyBox";
		m_sceneSkybox.addComponent<SkyBoxComponent>().load("texture://CUBE_MAP_HDR?assets/textures/hdr/little_paris_eiffel_tower_4k.hdr");

		//auto entity1 = createEntity();
		//entity1.getComponent<NameComponent>().name = "cube";
		//auto& v3d = entity1.addComponent<Visual3DComponent>();
		//v3d.mesh = dynamic_cast<Mesh*>(Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube"));
		//v3d.renderer = dynamic_cast<Renderer*>(Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/visual3d/visual3d.rdr"));
		//Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/box_diffuse.png",
		//	[=](Asset* asset)
		//	{
		//		auto& v3d = entity1.getComponent<Visual3DComponent>();
		//		v3d.texture2D = dynamic_cast<Texture2D*>(asset);
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
			//if (it->second.hasComponent<Visual3DComponent>())
			//{
			//	it->second.getComponent<Visual3DComponent>().release();
			//}

			if (it->second.hasComponent<PostProcessComponent>())
			{
				it->second.getComponent<PostProcessComponent>().unload();
			}			
			
			if (it->second.hasComponent<SkyBoxComponent>())
			{
				it->second.getComponent<SkyBoxComponent>().unload();
			}

			m_registry.destroy(it->first);
			m_entities.erase(id);
		}
	}

	void Scene::deleteAllEntity()
	{
		for (auto it = m_entities.begin(); it != m_entities.end();)
		{
			//if (it->second.hasComponent<Visual3DComponent>())
			//{
			//	it->second.getComponent<Visual3DComponent>().release();
			//}

			if (it->second.hasComponent<PostProcessComponent>())
			{
				it->second.getComponent<PostProcessComponent>().unload();
			}

			if (it->second.hasComponent<SkyBoxComponent>())
			{
				it->second.getComponent<SkyBoxComponent>().unload();
			}

			m_registry.destroy(it->first);
			it = m_entities.erase(it);
		}
	}

	void Scene::tick(float deltaTime)
	{

	}
}