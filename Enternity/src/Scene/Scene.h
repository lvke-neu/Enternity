#pragma once
#include "ECS/Entity.h"

namespace Enternity
{
	class CameraController;
	class Scene
	{
	public:
		Scene();
		~Scene();
	public:
		Entity createEntity();
		Entity getEntity(entt::entity id);
		void deleteEntity(entt::entity id);
		void tick(float deltaTime);
	private:
		entt::registry m_registry;
		std::unordered_map<entt::entity, Entity> m_entities;

		Entity m_sceneCamera;
		CameraController* m_cameraController{ nullptr };

		//TODO:
		Entity m_testVisual3DComponent;
		void onLoadFinish();
	};
}