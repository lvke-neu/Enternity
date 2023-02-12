/***************************************************************************************
Author: lvke
Date:2023/2/11 14:14
Description:
Scene
****************************************************************************************/
#pragma once
#include "ECS/Entity/Entity.h"
#include <unordered_map>

namespace Enternity
{
	struct Frustum;
	class Camera3D;
	class Scene
	{
		friend class RenderSystem;
	public:
		Scene();
		~Scene();
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
	public:
		Entity& createEntity();
		void deleteEntity(const std::string& uuid);
		void deleteAll();
	private:
		entt::registry m_registry;
		std::unordered_map<std::string, Entity> m_entities;
	//Scene basis
	public:
		void setFrustum(const Frustum& frustum);
	private:
		Camera3D* m_camera3D{ nullptr };
	};
}