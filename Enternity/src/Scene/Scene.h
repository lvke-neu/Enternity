#pragma once
#include "ECS/Entity.h"
#include <map>

namespace Enternity
{
	class FrameBuffer;
	class CameraController;
	class Mesh;
	class Scene
	{
		friend class RenderSystem;
	public:
		Scene();
		~Scene();
	public:
		Entity createEntity();
		Entity getEntity(entt::entity id);
		Entity getSceneCamera();
		const std::map<entt::entity, Entity>& getEntities();
		void deleteEntityById(entt::entity id);
		void deleteAllEntity();
		void tick(float deltaTime);
	private:
		entt::registry m_registry;
		std::map<entt::entity, Entity> m_entities;

		Entity m_sceneCamera;
		Entity m_scenePostprocess;
		Entity m_sceneSkybox;
		Entity m_scenePointLight;
		CameraController* m_cameraController{ nullptr };
	};

	inline Entity Scene::getSceneCamera()
	{
		return m_sceneCamera;
	}

	inline const std::map<entt::entity, Entity>& Scene::getEntities()
	{
		return m_entities;
	}
}