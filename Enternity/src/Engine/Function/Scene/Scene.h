/***************************************************************************************
Author: lvke
Date:2023/2/11 14:14
Description:
Scene
****************************************************************************************/
#pragma once
#include "Entity.h"
#include <unordered_map>
#include <string>

namespace Enternity
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene();
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
	public:
		std::string createEntity();
		void deleteEntity(const std::string& uuid);
		void deleteAll();

		entt::registry* getRegistry();
	private:
		entt::registry m_registry;
		std::unordered_map<std::string, Entity> m_entities;
	};
}