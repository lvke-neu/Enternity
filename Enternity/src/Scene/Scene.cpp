#include "Scene.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/NameComponent.h"
#include "ECS/PostProcessComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Common/Macro.h"
#include "CameraController.h"

namespace Enternity
{
	Scene::Scene()
	{
		//scene camera
		m_sceneCamera = createEntity();
		m_sceneCamera.getComponent<NameComponent>().name = "Camera";
		auto& comp = m_sceneCamera.addComponent<TransformComponent>();
		comp.translation = glm::vec3(0.28, 8.41, 19.70);
		comp.rotation = glm::vec3(-6.20, -11.00, 0);
		m_sceneCamera.addComponent<CameraComponent>().moveSpeed = 30;
		m_cameraController = new CameraController(&m_sceneCamera);

		m_scenePostprocess = createEntity();
		m_scenePostprocess.getComponent<NameComponent>().name = "PostProcess";
		auto& ppc = m_scenePostprocess.addComponent<PostProcessComponent>();
		ppc.mesh = dynamic_cast<Mesh*>(Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=plane"));
		ppc.renderer = dynamic_cast<Renderer*>(Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/postprocess/postprocess.rdr"));
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
				it->second.getComponent<PostProcessComponent>().release();
			}			
			
			//if (it->second.hasComponent<SkyboxComponent>())
			//{
			//	it->second.getComponent<SkyboxComponent>().release();
			//}

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
				it->second.getComponent<PostProcessComponent>().release();
			}

			//if (it->second.hasComponent<SkyboxComponent>())
			//{
			//	it->second.getComponent<SkyboxComponent>().release();
			//}

			m_registry.destroy(it->first);
			it = m_entities.erase(it);
		}
	}

	void Scene::tick(float deltaTime)
	{

	}
}