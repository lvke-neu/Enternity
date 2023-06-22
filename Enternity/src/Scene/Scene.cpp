#include "Scene.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "Common/Macro.h"
#include "CameraController.h"

namespace Enternity
{
	Scene::Scene()
	{
		m_sceneCamera = createEntity();
		
		m_sceneCamera.addComponent<TransformComponent>();
		m_sceneCamera.addComponent<CameraComponent>();

		m_cameraController = new CameraController(&m_sceneCamera);
	}

	Scene::~Scene()
	{
		for (auto& entity : m_entities)
		{
			m_registry.destroy(entity.second.getEnttID());
		}
		m_entities.clear();

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

	void Scene::deleteEntity(entt::entity id)
	{
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			m_entities.erase(id);
		}
	}

	void Scene::onUpdateTime(float deltaTime)
	{
		auto& cameraComponent = m_sceneCamera.getComponent<CameraComponent>();
		auto& transformComponent = m_sceneCamera.getComponent<TransformComponent>();
		int i = 0;
		i++;
	}
}