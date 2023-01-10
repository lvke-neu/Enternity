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
	Entity(entt::registry* registry,const std::string& name = "");

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
	entt::registry* m_pSceneRegistry;
	entt::entity m_EntityUid;
	std::string m_Name;
};

END_ENTERNITY