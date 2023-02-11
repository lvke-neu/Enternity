/***************************************************************************************
Author: lvke
Date:2023/2/11 14:09
Description:
Entity
****************************************************************************************/
#pragma once
#include <entt.hpp>

namespace Enternity
{
	class Scene;
	class Entity
	{
	public:
		Entity() = default;
		Entity(Scene* scene);
		~Entity() = default;
		Entity(const Entity&) = default;
		Entity& operator=(const Entity&) = default;
	public:
		entt::entity getEnttId();
	private:
		Scene* m_scene{ nullptr };
		entt::entity m_enttId{ entt::null };
	};
}