#include "Scene.h"
#include "Core/Basic/Macro.h"
#include "Core/Log/Log.h"
#include "Camera3D.h"

namespace Enternity
{
	Scene::Scene()
	{
		m_camera3D = new Camera3D;
	}

	Scene::~Scene()
	{
		deleteAll();
		SAFE_DELETE_SET_NULL(m_camera3D);
	}

	Entity& Scene::createEntity()
	{
		Entity entity(&m_registry);
		m_entities[entity.getUUID()] = entity;
		return m_entities[entity.getUUID()];
	}

	void Scene::deleteEntity(const std::string& uuid)
	{
		if (m_entities.find(uuid) != m_entities.end())
		{
			auto& entity = m_entities[uuid];
			m_registry.destroy(entity.getEnttId());
			m_entities.erase(uuid);
		}
		else
			LOG_ERROR("uuid:{0} entity doesn't exist in the scene", uuid);
	}

	void Scene::deleteAll()
	{
		for (auto& entity : m_entities)
		{
			m_registry.destroy(entity.second.getEnttId());
		}
		m_entities.clear();
	}

	entt::registry* Scene::getRegistry()
	{
		return &m_registry;
	}

	void Scene::setFrustum(const Frustum& frustum)
	{
		ENTERNITY_ASSERT(m_camera3D);
		m_camera3D->setFrustum(frustum);
	}
}