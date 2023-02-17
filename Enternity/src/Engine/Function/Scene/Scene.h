/***************************************************************************************
Author: lvke
Date:2023/2/11 14:14
Description:
Scene
****************************************************************************************/
#pragma once
#include "ECS/Entity/Entity.h"
#include "Camera/CameraController.h"
#include <unordered_map>

namespace Enternity
{
	class Scene
	{
		friend class RenderSystem;
		friend class SceneManager;
	public:
		Scene();
		~Scene();
		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;
	public:
		void tick();
		Entity& createEntity();
		void deleteEntity(const std::string& uuid);
		void deleteAll();

	private:
		void loadResource();
	private:
		entt::registry m_registry;
		std::unordered_map<std::string, Entity> m_entities;

		Camera3D* m_camera3D{ nullptr };
		CameraController m_cameraController;
	};
}