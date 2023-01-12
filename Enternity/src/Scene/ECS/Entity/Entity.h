/***************************************************************************************
Author: lvke
Date:2023/1/10 20:00
Description:
Entity : use singleton scenemanager's registry
****************************************************************************************/
#pragma once

#include <entt.hpp>
#include "Macro/Macro.h"

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
		auto& registry = *m_pSceneRegistry;
		return registry.emplace<T>(m_EntityUid, std::forward<Args>(args)...);
	}

	template<typename T, typename...Args>
	void RemoveComponent(Args&& ... args)
	{
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
private:
	entt::registry* m_pSceneRegistry{ nullptr };
	entt::entity m_EntityUid{ entt::null };
};

END_ENTERNITY