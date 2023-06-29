#include "Scene.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/Visual3DComponent.h"
#include "ECS/NameComponent.h"
#include "ECS/PostprocessComponent.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Mesh/MeshProvider.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/RendererProvider.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/TextureProvider.h"
#include "Common/Macro.h"
#include "CameraController.h"


namespace Enternity
{
	Scene::Scene()
	{
		//scene camera
		m_sceneCamera = createEntity();
		m_sceneCamera.getComponent<NameComponent>().name = "Camera";
		auto& comp = m_sceneCamera.addComponent<TransformComponent>();
		comp.translation = glm::vec3(0, 0, 19);
		comp.rotation = glm::vec3(21, 0, 0);
		m_sceneCamera.addComponent<CameraComponent>();
		m_cameraController = new CameraController(&m_sceneCamera);

		//postprocess
		m_scenePostprocess = createEntity();
		m_scenePostprocess.getComponent<NameComponent>().name = "Postprocess";
		auto& ppc = m_scenePostprocess.addComponent<PostprocessComponent>();
		ppc.renderer = Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererSync("assets/shaders/postprocess/postprocess.vert", "assets/shaders/postprocess/postprocess.frag");
		ppc.mesh = Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshSync(BasicPrimitve::Quad);
		
		//test entity 1
		auto entity = createEntity();
		entity.getComponent<NameComponent>().name = "nanosuit";
		entity.addComponent<TransformComponent>();
		entity.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/nanosuit/nanosuit.obj",
			[=](Mesh* mesh)
			{
				auto& comp = entity.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});
		
		//test entity 2
		auto entity2 = createEntity();
		entity2.getComponent<NameComponent>().name = "planet";
		auto& tfc2 = entity2.addComponent<TransformComponent>();
		tfc2.translation = glm::vec3(10, 10, 0);
		entity2.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity2.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/planet/planet.obj",
			[=](Mesh* mesh)
			{
				auto& comp = entity2.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});

		//test entity 3
		auto entity3 = createEntity();
		entity3.getComponent<NameComponent>().name = "cube";
		entity3.addComponent<TransformComponent>();
		entity3.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity3.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		entity3.getComponent<Visual3DComponent>().mesh = Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshSync(BasicPrimitve::Box);
		/*Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/models/Cube.fbx",
			[=](Mesh* mesh)
			{
				auto& comp = entity3.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			})*/;

		//test entity 4
		auto entity4 = createEntity();
		entity4.getComponent<NameComponent>().name = "madara_uchiha";
		auto& tfc4 = entity4.addComponent<TransformComponent>();
		tfc4.translation = glm::vec3(-10, 10, 0);
		entity4.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity4.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/Madara_Uchiha/Madara_Uchiha.obj",
			[=](Mesh* mesh)
			{
				auto& comp = entity4.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});

		//test entity 5
		auto entity5 = createEntity();
		entity5.getComponent<NameComponent>().name = "pipe";
		auto& tfc5 = entity5.addComponent<TransformComponent>();
		tfc5.translation = glm::vec3(-10, 0, 0);
		entity5.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity5.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/models/Pipe.fbx",
			[=](Mesh* mesh)
			{
				auto& comp = entity5.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});

		//test entity 6
		auto entity6 = createEntity();
		entity6.getComponent<NameComponent>().name = "house";
		auto& tfc6 = entity6.addComponent<TransformComponent>();
		tfc6.translation = glm::vec3(-10, 5, 0);
		tfc6.scale = glm::vec3(0.01, 0.01, 0.01);
		entity6.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity6.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/house/house.obj",
			[=](Mesh* mesh)
			{
				auto& comp = entity6.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
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
			}
			m_entities.erase(id);
		}
	}

	void Scene::tick(float deltaTime)
	{

	}
}