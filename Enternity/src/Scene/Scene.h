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
		friend class ViewPortPanel;
	public:
		Scene();
		~Scene();
	public:
		Entity createEntity();
		Entity getEntity(entt::entity id);
		void deleteEntityById(entt::entity id);
		void deleteAllEntity();
		void tick(float deltaTime);
	private:
		entt::registry m_registry;
		std::unordered_map<entt::entity, Entity> m_entities;

		Entity m_sceneCamera;
		Entity m_scenePostprocess;
		Entity m_skybox;
		CameraController* m_cameraController{ nullptr };
	};
}