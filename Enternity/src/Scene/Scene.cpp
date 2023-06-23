#include "Scene.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/Visual3DComponent.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Mesh/MeshProvider.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/RendererProvider.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Texture/TextureProvider.h"
#include "Common/Macro.h"
#include "CameraController.h"


namespace Enternity
{
	Scene::Scene()
	{
		m_sceneCamera = createEntity();
		
		auto& comp = m_sceneCamera.addComponent<TransformComponent>();
		comp.translation = glm::vec3(0, 0, 20);
		m_sceneCamera.addComponent<CameraComponent>();

		m_cameraController = new CameraController(&m_sceneCamera);

		//TODO:
		m_testVisual3DComponent = createEntity();
		m_testVisual3DComponent.addComponent<TransformComponent>();
		auto& v3d  = m_testVisual3DComponent.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[&](Renderer* render)
			{
				auto& comp = m_testVisual3DComponent.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/nanosuit/nanosuit.obj", 
			[&](Mesh* mesh) 
			{
				auto& comp = m_testVisual3DComponent.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});
		Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTextureAsyn("assets/textures/box_diffuse.png",
			[&](Texture* texture)
			{
				auto& comp = m_testVisual3DComponent.getComponent<Visual3DComponent>();
				comp.texture = texture;
			});
		
		m_testVisual3DComponent2 = createEntity();
		m_testVisual3DComponent2.addComponent<TransformComponent>();
		auto& v3d2 = m_testVisual3DComponent2.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[&](Renderer* render)
			{
				auto& comp = m_testVisual3DComponent2.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/models/Cube.fbx",
			[&](Mesh* mesh)
			{
				auto& comp = m_testVisual3DComponent2.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});
		Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTextureAsyn("assets/textures/skybox.jpeg",
			[&](Texture* texture)
			{
				auto& comp = m_testVisual3DComponent2.getComponent<Visual3DComponent>();
				comp.texture = texture;
			});
	}

	Scene::~Scene()
	{
		for (auto& entity : m_entities)
		{
			m_registry.destroy(entity.second.getEnttID());
		}
		m_entities.clear();

		SAFE_DELETE_SET_NULL(m_cameraController);
	}

	Entity Scene::createEntity()
	{
		Entity entity(&m_registry);
		m_entities.insert({ entity.getEnttID(), entity });

		return entity;
	}

	Entity Scene::getEntity(entt::entity id)
	{
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			return m_entities[id];
		}

		return Entity();
	}

	void Scene::deleteEntity(entt::entity id)
	{
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			if (it->second.hasComponent<Visual3DComponent>())
			{
				SAFE_DELETE_SET_NULL(it->second.getComponent<Visual3DComponent>().mesh);
				SAFE_DELETE_SET_NULL(it->second.getComponent<Visual3DComponent>().renderer);
				SAFE_DELETE_SET_NULL(it->second.getComponent<Visual3DComponent>().texture);
			}
			m_entities.erase(id);
		}
	}

	void Scene::tick(float deltaTime)
	{

	}
}