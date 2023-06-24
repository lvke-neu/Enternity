#pragma once
#include "ECS/Entity.h"

namespace Enternity
{
	class FrameBuffer;
	class CameraController;
	class Mesh;
	class Scene
	{
		friend class RenderSystem;
		friend class ScenePanel;
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
	};
}