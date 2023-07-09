#include "Scene.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/Visual3DComponent.h"
#include "ECS/NameComponent.h"
#include "ECS/PostprocessComponent.h"
#include "ECS/SkyboxComponent.h"
#include "ECS/ParticleComponent.h"
#include "Engine/Engine.h"
#include "Engine/Blob.h"
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
		comp.translation = glm::vec3(0.28, 8.41, 19.70);
		comp.rotation = glm::vec3(-6.20, -11.00, 0);
		m_sceneCamera.addComponent<CameraComponent>().moveSpeed = 30;
		m_cameraController = new CameraController(&m_sceneCamera);

		//postprocess
		m_scenePostprocess = createEntity();
		m_scenePostprocess.getComponent<NameComponent>().name = "Postprocess";
		auto& ppc = m_scenePostprocess.addComponent<PostprocessComponent>();
		ppc.renderer = Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererSync("assets/shaders/postprocess/postprocess.vert", "assets/shaders/postprocess/postprocess.frag");
		ppc.mesh = Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshSync(BasicMeshType::Quad);
		
		m_skybox = createEntity();
		m_skybox.getComponent<NameComponent>().name = "Skybox";
		m_skybox.addComponent<SkyboxComponent>().skyboxType = SkyboxComponent::SkyboxType::Daylight;
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn(BasicMeshType::Box,
			[=](Mesh* mesh)
			{
				auto& comp = m_skybox.getComponent<SkyboxComponent>();
				comp.mesh = mesh;
			});
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/skybox/skybox.vert", "assets/shaders/skybox/skybox.frag",
			[=](Renderer* render)
			{
				auto& comp = m_skybox.getComponent<SkyboxComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getCubeMapTextureAsyn(SkyboxComponent::FullPaths[SkyboxComponent::SkyboxType::Daylight],
			[=](CubeMapTexture* cubeMapTexture)
			{
				auto& comp = m_skybox.getComponent<SkyboxComponent>();
				comp.cubeMapTexture = cubeMapTexture;
			});
		
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
		entity3.getComponent<NameComponent>().name = "floor";
		entity3.addComponent<TransformComponent>().scale = glm::vec3(200, 0, 200);
		entity3.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/floor.frag",
			[=](Renderer* render)
			{
				auto& comp = entity3.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/basic/Cube.fbx",
			[=](Mesh* mesh)
			{
				auto& comp = entity3.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});

		//test entity 4
		auto entity4 = createEntity();
		entity4.getComponent<NameComponent>().name = "madara_uchiha";
		auto& tfc4 = entity4.addComponent<TransformComponent>();
		tfc4.translation = glm::vec3(22.44, 0, -4.13);
		tfc4.scale = glm::vec3(4.00, 4.00, 4.00);
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
		entity5.getComponent<NameComponent>().name = "sponza";
		auto& tfc5 = entity5.addComponent<TransformComponent>();
		tfc5.translation = glm::vec3(-22.85, 5.07, -41.99);
		tfc5.scale = glm::vec3(0.01, 0.01, 0.01);
		entity5.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity5.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/sponzapbr/Sponza.gltf",
			[=](Mesh* mesh)
			{
				auto& comp = entity5.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});

		//test entity 6
		auto entity6 = createEntity();
		entity6.getComponent<NameComponent>().name = "house";
		auto& tfc6 = entity6.addComponent<TransformComponent>();
		tfc6.translation  = glm::vec3(51.49, 2.68, -39.41);
		tfc6.scale = glm::vec3(0.05, 0.05, 0.05);
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

		//test entity 7
		auto entity7 = createEntity();
		entity7.getComponent<NameComponent>().name = "tree";
		auto& tfc7 = entity7.addComponent<TransformComponent>();
		tfc7.translation = glm::vec3(5.26, 2.76, -50.18);
		tfc7.scale = glm::vec3(0.03f);
		entity7.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/tree.frag",
			[=](Renderer* render)
			{
				auto& comp = entity7.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/tree/tree.obj",
			[=](Mesh* mesh)
			{
				auto& comp = entity7.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});

		auto entity8 = createEntity();
		entity8.getComponent<NameComponent>().name = "jeep";
		auto& tfc8 = entity8.addComponent<TransformComponent>();
		tfc8.translation = glm::vec3(-10.60, 3.57, 3.04);
		tfc8.scale = glm::vec3(0.01, 0.01, 0.01);
		entity8.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity8.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/jeep/jeep.obj",
			[=](Mesh* mesh)
			{
				auto& comp = entity8.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});

		auto entity9 = createEntity();
		entity9.getComponent<NameComponent>().name = "hheli";
		auto& tfc9 = entity9.addComponent<TransformComponent>();
		tfc9.translation = glm::vec3(-27.68, 0, -19.98);
		tfc9.scale = glm::vec3(0.10, 0.10, 0.10);
		entity9.addComponent<Visual3DComponent>();
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/test/test2.vert", "assets/shaders/test/test2.frag",
			[=](Renderer* render)
			{
				auto& comp = entity9.getComponent<Visual3DComponent>();
				comp.renderer = render;
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn("assets/models/hheli/hheli.obj",
			[=](Mesh* mesh)
			{
				auto& comp = entity9.getComponent<Visual3DComponent>();
				comp.mesh = mesh;
			});


		//test particle 
		auto particle = createEntity();
		particle.getComponent<NameComponent>().name = "particle";
		auto& tfcparticle = particle.addComponent<TransformComponent>();
		tfcparticle.translation = glm::vec3(0, 5, 5);
		particle.addComponent<ParticleComponent>().renderer;
		Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRendererAsyn("assets/shaders/particle/particle.vert", "assets/shaders/particle/particle.frag",
			[=](Renderer* render)
			{
				auto& comp = particle.getComponent<ParticleComponent>();
				comp.renderer = render;
				comp.renderer->setRenderPass({ RenderPass::Fill, true, true });
			});
		Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMeshAsyn(BasicMeshType::Quad,
			[=](Mesh* mesh)
			{
				auto& comp = particle.getComponent<ParticleComponent>();
				comp.mesh = mesh;
			});
		int width = 256;
		int height = 256;
		int channels = 4;
		Blob data(width * height * channels);
		float maxDistance = std::sqrtf((float)width * height + (float)width * height) / 2.0f;
		for (int x = 0; x < height; ++x)
		{
			for (int y = 0; y < width; ++y)
			{
				float deltaX = x - height / 2.0f;
				float deltaY = y - width / 2.0f;
				float distance = std::sqrtf(deltaX* deltaX + deltaY * deltaY);

				unsigned char r = 255;
				unsigned char g = 255;
				unsigned char b = 255;
				unsigned char a = (unsigned char)(std::powf(1.0f - (distance / maxDistance), 4.0f) * 255);

				int currentPixel = (x * height + y) * channels;
				*((char*)data.getData() + currentPixel) = r;
				*((char*)data.getData() + currentPixel + 1) = g;
				*((char*)data.getData() + currentPixel + 2) = b;
				*((char*)data.getData() + currentPixel + 3) = a;
			}
		}
		particle.getComponent<ParticleComponent>().texture =
			Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTextureFromData(&data, width, height, channels);
	}

	Scene::~Scene()
	{
		deleteAllEntity();

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


	void Scene::deleteEntityById(entt::entity id)
	{
		//auto it = m_entities.find(id);
		//if (it != m_entities.end())
		//{
		//	if (it->second.hasComponent<Visual3DComponent>())
		//	{
		//		it->second.getComponent<Visual3DComponent>().release();
		//	}

		//	if (it->second.hasComponent<PostprocessComponent>())
		//	{
		//		it->second.getComponent<PostprocessComponent>().release();
		//	}			
		//	
		//	if (it->second.hasComponent<SkyboxComponent>())
		//	{
		//		it->second.getComponent<SkyboxComponent>().release();
		//	}

		//	m_registry.destroy(it->first);
		//	m_entities.erase(id);
		//}
	}

	void Scene::deleteAllEntity()
	{
		for (auto it = m_entities.begin(); it != m_entities.end();)
		{
			if (it->second.hasComponent<Visual3DComponent>())
			{
				it->second.getComponent<Visual3DComponent>().release();
			}

			if (it->second.hasComponent<PostprocessComponent>())
			{
				it->second.getComponent<PostprocessComponent>().release();
			}

			if (it->second.hasComponent<SkyboxComponent>())
			{
				it->second.getComponent<SkyboxComponent>().release();
			}

			m_registry.destroy(it->first);
			it = m_entities.erase(it);
		}
	}

	void Scene::tick(float deltaTime)
	{

	}
}