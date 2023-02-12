#include "SceneManager.h"
#include "Function/Scene/ECS/Component/MeshRenderComponent.hpp"
#include "Function/Render/RenderSystem.h"
#include "Core/ThreadPool/ThreadPool.h"

namespace Enternity
{
	void SceneManager::initialize()
	{
		auto& entity = m_scene.createEntity();
		auto& comp = entity.addComponent<AsynLoadTestComponent>();

		ThreadPool::GetInstance().commitTask(
			[&]() 
			{
				BlobLoader blobLoader;
			
				Sleep(5000);
				comp.m_blob = blobLoader.load(comp.m_texture, AssetType::Texture);
			});

		LOG_INFO("SceneManager initialization");
	}

	void SceneManager::uninitialize()
	{
		LOG_INFO("SceneManager uninitialization");
	}

	void SceneManager::tick()
	{
		auto& entity = m_scene.m_entities.begin()->second;
		auto& comp = entity.getComponent<AsynLoadTestComponent>();
		if (comp.m_blob)
		{
			comp.load();
			LOG_INFO("load finished");
		}

		RenderSystem::GetInstance().drawCall(&m_scene);
	}

	void SceneManager::setFrustum(const Frustum& frustum)
	{
		m_scene.setFrustum(frustum);
	}
}