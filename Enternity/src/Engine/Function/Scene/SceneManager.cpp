#include "SceneManager.h"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
#include "Function/Render/RenderSystem.h"
#include "Function/Scene/Camera/Camera3D.h"
#include "Core/File/BlobLoader.h"

namespace Enternity
{
	void SceneManager::initialize()
	{
		m_scene.m_camera3D->setPosition(Vector3f(0,0,34));

		auto& entity = m_scene.createEntity();

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

		LOG_INFO("SceneManager initialization");
	}

	void SceneManager::uninitialize()
	{
		LOG_INFO("SceneManager uninitialization");
	}

	void SceneManager::loadResource()
	{
		auto viewShaderComponent = m_scene.m_registry.view<ShaderComponent>();
		for (auto entity : viewShaderComponent)
		{
			auto& comp = viewShaderComponent.get<ShaderComponent>(entity);
			comp.loadImpl();
		}

		auto viewMaterialComponent = m_scene.m_registry.view<MaterialComponent>();
		for (auto entity : viewMaterialComponent)
		{
			auto& comp = viewMaterialComponent.get<MaterialComponent>(entity);
			comp.loadImpl();
		}
		
		auto viewMeshComponent = m_scene.m_registry.view<MeshComponent>();
		for (auto entity : viewMeshComponent)
		{
			auto& comp = viewMeshComponent.get<MeshComponent>(entity);
			comp.loadImpl();
		}
	}

	void SceneManager::tick()
	{
		loadResource();

		RenderSystem::GetInstance().drawCall(&m_scene);
	}

	void SceneManager::setFrustum(const Frustum& frustum)
	{
		m_scene.setFrustum(frustum);
	}
}