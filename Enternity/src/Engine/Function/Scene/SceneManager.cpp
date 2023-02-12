#include "SceneManager.h"
#include "Function/Scene/ECS/Component/MeshRenderComponents.hpp"
#include "Function/Render/RenderSystem.h"
#include "Core/File/BlobLoader.h"

namespace Enternity
{
	void SceneManager::initialize()
	{
		auto& entity = m_scene.createEntity();

		auto& comp = entity.addComponent<ShaderComponent>();
		comp.m_vsShaderFile = "assets/shaders/Phong.vert";
		comp.m_psShaderFile = "assets/shaders/Phong.frag";
		BlobLoader blobLoader1;
		blobLoader1.load(comp.m_vsBlob, comp.m_vsShaderFile, AssetType::General, LoadType::Asyn);
		BlobLoader blobLoader2;
		blobLoader2.load(comp.m_psBlob, comp.m_psShaderFile, AssetType::General, LoadType::Asyn);

		auto& comp2 = entity.addComponent<MaterialComponent>();
		comp2.m_textureFile = "assets/textures/box_diffuse.png";
		BlobLoader blobLoader3;
		blobLoader3.load(comp2.m_textureBlob, comp2.m_textureFile, AssetType::Texture, LoadType::Asyn);

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
		comp.loadImpl();
		comp2.loadImpl();

		RenderSystem::GetInstance().drawCall(&m_scene);
	}

	void SceneManager::setFrustum(const Frustum& frustum)
	{
		m_scene.setFrustum(frustum);
	}
}