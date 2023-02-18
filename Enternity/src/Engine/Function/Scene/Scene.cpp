#include "Scene.h"
#include "Camera/Camera3D.h"
#include "ECS/Component/TagComponent.hpp"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
#include "Core/Asset/AssetLoader.h"
#include "Function/Render/RenderSystem.h"

namespace Enternity
{
	Scene::Scene()
	{
		m_camera3D = new Camera3D;
		m_cameraController.attachCamera3D(m_camera3D);

		m_camera3D->setPosition(Vector3f(0, 0, 34));

		auto& entity = createEntity();

		auto& comp = entity.addComponent<ShaderComponent>();
		comp.m_shaderAssetImpl = new ShaderAssetImpl;
		comp.m_shaderAssetImpl->load("assets/shaders/Phong.vert", "assets/shaders/Phong.frag");


		auto& comp2 = entity.addComponent<MaterialComponent>();
		comp2.m_textureAssetImpl = new TextureAssetImpl;
		comp2.m_textureAssetImpl->load("assets/textures/box_diffuse.png");

		auto& comp3 = entity.addComponent<MeshComponent>();
		comp3.m_MeshAssetImpl = new MeshAssetImpl;
		comp3.m_MeshAssetImpl->load("assets/models/nanosuit/nanosuit.obj");
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