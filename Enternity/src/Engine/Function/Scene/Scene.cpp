#include "Scene.h"
#include "Function/Scene/Camera/Camera3D.h"
#include "Function/Scene/ECS/Component/TagComponent.h"
#include "Function/Scene/ECS/Component/Visual3DComponent.h"
#include "Function/Scene/ECS/Component/TransformComponent.h"
#include "Function/Render/RenderSystem.h"
#include "Core/Asset/AssetLoader.h"


namespace Enternity
{
	Scene::Scene()
	{
		m_camera3D = new Camera3D;
		m_cameraController.attachCamera3D(m_camera3D);

		m_camera3D->setPosition(Vector3f(0, 0, 34));


		auto& entity2 = createEntity();

		auto& trans = entity2.addComponent<TransformComponent>();
		trans.m_scale = Vector3f(100, 0.5, 100);
		trans.m_position.y = -5.0f;

		auto& comp2 = entity2.addComponent<Visual3DComponent>();
		comp2.m_rendererPassAssetImpl->load("assets/shaders/Phong.vert", "assets/shaders/Phong2.frag");
		comp2.m_textureAssetImpl->load("assets/textures/box_diffuse.png");
		comp2.m_MeshAssetImpl->load("assets/models/Box.fbx");
		comp2.m_rendererPassAssetImpl->setRenderState(RenderState::WireFrame, true);




		//for (int i = 0; i < 2000; i++)
		//{
			auto& entity = createEntity();
			auto& trans2 = entity.addComponent<TransformComponent>();
			//trans.m_position.x += i;

			auto& comp = entity.addComponent<Visual3DComponent>();

			comp.m_rendererPassAssetImpl->load("assets/shaders/Phong.vert", "assets/shaders/Phong.frag");
			comp.m_textureAssetImpl->load("assets/textures/box_diffuse.png");
			comp.m_MeshAssetImpl->load("assets/models/nanosuit/nanosuit.obj");
		//}




	}

	Scene::~Scene()
	{
		deleteAll();
		SAFE_DELETE_SET_NULL(m_camera3D);
	}

	void Scene::tick()
	{
		RenderSystem::GetInstance().drawCall(this);
	}

	Entity& Scene::createEntity()
	{
		Entity entity(&m_registry);
		entity.addComponent<TagComponent>();
		m_entities[entity.getUUID()] = entity;
		return m_entities[entity.getUUID()];
	}

	void Scene::deleteEntity(const std::string& uuid)
	{
		if (m_entities.find(uuid) != m_entities.end())
		{
			auto& entity = m_entities[uuid];
			m_registry.destroy(entity.getEnttId());
			m_entities.erase(uuid);
		}
		else
			LOG_ERROR("uuid:{0} entity doesn't exist in the scene", uuid);
	}

	void Scene::deleteAll()
	{
		for (auto& entity : m_entities)
		{
			m_registry.destroy(entity.second.getEnttId());
		}
		m_entities.clear();
	}
}