#include "SceneManager.h"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
#include "Function/Render/RenderSystem.h"
#include "Function/Scene/Camera3D.h"
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

	void SceneManager::tick()
	{
		auto& entity = m_scene.m_entities.begin()->second;
		
		auto& comp = entity.getComponent<ShaderComponent>();
		auto& comp2 = entity.getComponent<MaterialComponent>();
		auto& comp3 = entity.getComponent<MeshComponent>();
		comp.loadImpl();
		comp2.loadImpl();
		comp3.loadImpl();

		RenderSystem::GetInstance().drawCall(&m_scene);
	}

	void SceneManager::setFrustum(const Frustum& frustum)
	{
		m_scene.setFrustum(frustum);
	}
}