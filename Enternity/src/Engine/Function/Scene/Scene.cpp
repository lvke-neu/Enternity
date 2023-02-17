#include "Scene.h"
#include "Core/File/BlobLoader.h"
#include "Camera/Camera3D.h"
#include "ECS/Component/TagComponent.hpp"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
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
		comp.m_vsShaderFile = "assets/shaders/Phong.vert";
		comp.m_psShaderFile = "assets/shaders/Phong.frag";

		auto& comp2 = entity.addComponent<MaterialComponent>();
		comp2.m_textureFile = "assets/textures/box_diffuse.png";

		auto& comp3 = entity.addComponent<MeshComponent>();
		comp3.m_meshFile = "assets/models/nanosuit/nanosuit.obj";
		//comp3.m_meshFile = "assets/models/models/Cube.fbx";

		BlobLoader blobLoader;
		blobLoader.loadGeneral(comp.m_vsBlob, comp.m_vsShaderFile, LoadType::Asyn);
		blobLoader.loadGeneral(comp.m_psBlob, comp.m_psShaderFile, LoadType::Asyn);
		blobLoader.loadTexture(comp2.m_textureBlob, comp2.m_textureFile, LoadType::Asyn);
		blobLoader.loadMesh(comp3.m_vertexbufferBlob, comp3.m_indexbufferBlob, comp3.m_meshFile, LoadType::Asyn);
	}

	Scene::~Scene()
	{
		deleteAll();
		SAFE_DELETE_SET_NULL(m_camera3D);
	}

	void Scene::loadResource()
	{
		auto viewShaderComponent = m_registry.view<ShaderComponent>();
		for (auto entity : viewShaderComponent)
		{
			auto& comp = viewShaderComponent.get<ShaderComponent>(entity);
			comp.loadImpl();
		}

		auto viewMaterialComponent = m_registry.view<MaterialComponent>();
		for (auto entity : viewMaterialComponent)
		{
			auto& comp = viewMaterialComponent.get<MaterialComponent>(entity);
			comp.loadImpl();
		}

		auto viewMeshComponent = m_registry.view<MeshComponent>();
		for (auto entity : viewMeshComponent)
		{
			auto& comp = viewMeshComponent.get<MeshComponent>(entity);
			comp.loadImpl();
		}
	}

	void Scene::tick()
	{
		loadResource();

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