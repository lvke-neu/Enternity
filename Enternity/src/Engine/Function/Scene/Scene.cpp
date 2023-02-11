#include "Scene.h"
#include "Core/Basic/UUID.h"
#include "Core/Log/Log.h"

namespace Enternity
{

	Scene::~Scene()
	{
		deleteAll();
	}

	std::string Scene::createEntity()
	{
		std::string uuid = UUID::Generate();
		m_entities[uuid] = Entity(this);
		return uuid;
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
}