#include "Scene.h"
#include "ECS/TransformComponent.h"
#include "ECS/CameraComponent.h"
#include "ECS/NameComponent.h"
#include "ECS/PostProcessComponent.h"
#include "ECS/SkyBoxComponent.h"
#include "ECS/Visual3DComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Renderer/Renderer.h"
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

		m_scenePostprocess = createEntity();
		m_scenePostprocess.getComponent<NameComponent>().name = "PostProcess";
		auto& ppc = m_scenePostprocess.addComponent<PostProcessComponent>();
		ppc.mesh = dynamic_cast<Mesh*>(Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=plane"));
		ppc.renderer = dynamic_cast<Renderer*>(Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/postprocess/postprocess.rdr"));

		m_sceneSkybox = createEntity();
		m_sceneSkybox.getComponent<NameComponent>().name = "SkyBox";
		auto& skybox = m_sceneSkybox.addComponent<SkyBoxComponent>();
		skybox.mesh = dynamic_cast<Mesh*>(Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube"));
		skybox.renderer = dynamic_cast<Renderer*>(Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/skybox/skybox.rdr"));
		Engine::GetInstance().getAssetLoader()->getAsset("texture://CUBE_MAP?assets/textures/skybox/daylight/.png",
			[&](Asset* asset)
			{
				auto& skybox = m_sceneSkybox.getComponent<SkyBoxComponent>();
				skybox.textureCubeMap = dynamic_cast<TextureCubeMap*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://CUBE_MAP_HDR?assets/textures/hdr/newport_loft.hdr",
			[&](Asset* asset)
			{
				auto& skybox = m_sceneSkybox.getComponent<SkyBoxComponent>();
				skybox.textureCubeMapHDR = dynamic_cast<TextureCubeMapHDR*>(asset);
			});
		//skybox.textureCubeMapHDR = dynamic_cast<TextureCubeMapHDR*>(Engine::GetInstance().getAssetLoader()->getAsset("texture://CUBE_MAP_HDR?assets/textures/hdr/newport_loft.hdr"));
		//auto entity1 = createEntity();
		//entity1.getComponent<NameComponent>().name = "hdr test";
		//auto& v3d = entity1.addComponent<Visual3DComponent>();
		//v3d.mesh = dynamic_cast<Mesh*>(Engine::GetInstance().getAssetLoader()->getAsset("mesh://primitive=cube"));
		//v3d.renderer = dynamic_cast<Renderer*>(Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/hdr/hdr.rdr"));
		//Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D_HDR?assets/textures/hdr/spree_bank_4k.hdr",
		//	[=](Asset* asset)
		//	{
		//		auto& v3d = entity1.getComponent<Visual3DComponent>();
		//		v3d.texture2D = dynamic_cast<Texture2D*>(asset);
		//	});
		
		//v3d.texture2D = dynamic_cast<Texture2D*>(Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D_HDR?assets/textures/hdr/blue_photo_studio_4k.hdr"));
		//auto asset = dynamic_cast<TextureCubeMapHDR*>(Engine::GetInstance().getAssetLoader()->getAsset("texture://CUBE_MAP_HDR?assets/textures/hdr/blue_photo_studio_4k.hdr"));
		//int i = 0;
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
		auto it = m_entities.find(id);
		if (it != m_entities.end())
		{
			//if (it->second.hasComponent<Visual3DComponent>())
			//{
			//	it->second.getComponent<Visual3DComponent>().release();
			//}

			if (it->second.hasComponent<PostProcessComponent>())
			{
				it->second.getComponent<PostProcessComponent>().release();
			}			
			
			if (it->second.hasComponent<SkyBoxComponent>())
			{
				it->second.getComponent<SkyBoxComponent>().release();
			}

			m_registry.destroy(it->first);
			m_entities.erase(id);
		}
	}

	void Scene::deleteAllEntity()
	{
		for (auto it = m_entities.begin(); it != m_entities.end();)
		{
			//if (it->second.hasComponent<Visual3DComponent>())
			//{
			//	it->second.getComponent<Visual3DComponent>().release();
			//}

			if (it->second.hasComponent<PostProcessComponent>())
			{
				it->second.getComponent<PostProcessComponent>().release();
			}

			if (it->second.hasComponent<SkyBoxComponent>())
			{
				it->second.getComponent<SkyBoxComponent>().release();
			}

			m_registry.destroy(it->first);
			it = m_entities.erase(it);
		}
	}

	void Scene::tick(float deltaTime)
	{

	}
}