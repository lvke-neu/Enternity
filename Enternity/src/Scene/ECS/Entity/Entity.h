/***************************************************************************************
Author: lvke
Date:2023/1/10 20:00
Description:
Entity : use singleton scenemanager's registry
****************************************************************************************/
#pragma once

#include <entt.hpp>
#include "Macro/Macro.h"
#include "Log/Log.h"

BEGIN_ENTERNITY

class Entity
{
public:
	Entity() = default;

	//create an entity that does not exist
	Entity(entt::registry* registry,const std::string& name = "");

	//initialize an enitity that is exist
	Entity(entt::registry* registry, entt::entity entityUid);

	template<typename T, typename...Args>
	T& AddComponent(Args&& ... args)
	{
		if (HasComponent<T>())
		{
			LOG_ERROR("Component has exist in this Entity");
			return GetComponent<T>();
		}
		auto& registry = *m_pSceneRegistry;
		return registry.emplace<T>(m_EntityUid, std::forward<Args>(args)...);
	}

	template<typename T, typename...Args>
	void RemoveComponent(Args&& ... args)
	{
		if (!HasComponent<T>())
		{
			LOG_ERROR("Component doesn't exist in this Entity");
			return ;
		}
		auto& registry = *m_pSceneRegistry;
		return registry.remove<T>(m_EntityUid);
	}

	template<typename T>
	T& GetComponent()
	{
		auto& registry = *m_pSceneRegistry;
		return registry.get<T>(m_EntityUid);
	}

	template <typename T>
	bool HasComponent()
	{
		auto& registry = *m_pSceneRegistry;
		return registry.has<T>(m_EntityUid);
	}

	uint32_t GetEntityUid()
	{
		return (uint32_t)m_EntityUid;
	}

	bool operator== (const Entity& entity)
	{
		return (m_pSceneRegistry == entity.m_pSceneRegistry) && (m_EntityUid == entity.m_EntityUid);
	}

	bool operator!= (const Entity& entity)
	{
		return ! operator== (entity);
	}

	bool IsValidEntity()
	{
		return m_EntityUid != entt::null;
	}

	void Destroy()
	{
		m_pSceneRegistry->destroy(m_EntityUid);
	}

private:
	entt::registry* m_pSceneRegistry{ nullptr };
	entt::entity m_EntityUid{ entt::null };
};

END_ENTERNITY