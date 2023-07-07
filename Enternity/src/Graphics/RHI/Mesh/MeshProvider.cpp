#include "MeshProvider.h"
#include "Mesh.h"
#include "MeshAsset.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Engine/Event/EventSystem.h"

namespace Enternity
{
	MeshProvider::MeshProvider()
	{
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::Tick, BIND(MeshProvider::tick));
	}

	MeshProvider::~MeshProvider()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::Tick, BIND(MeshProvider::tick));
	}

	Mesh* MeshProvider::getMeshSync(const char* fullPath)
	{
		Mesh* mesh = nullptr;

		MeshAsset* meshAsset = new MeshAsset(fullPath);
		meshAsset->load(0);

		if (meshAsset->getLoadingState() == Asset::LoadingState::loading_state_succeeded)
		{
			mesh = new Mesh(meshAsset);
		}

		SAFE_DELETE_SET_NULL(meshAsset);

		return mesh;
	}

	Mesh* MeshProvider::getMeshSync(BasicMeshType type, const std::string& texturePath)
	{
		Mesh* mesh = nullptr;

		BasicMeshAsset* basicMeshAsset = new BasicMeshAsset(type, texturePath);
		basicMeshAsset->load(0);

		if (basicMeshAsset->getLoadingState() == Asset::LoadingState::loading_state_succeeded)
		{
			mesh = new Mesh(basicMeshAsset);
		}

		SAFE_DELETE_SET_NULL(basicMeshAsset);

		return mesh;
	}

	void MeshProvider::getMeshAsyn(const char* fullPath, std::function<void(Mesh*)> callback)
	{
		MeshAsset* meshAsset = new MeshAsset(fullPath);
		meshAsset->load();

		m_map.push_back({meshAsset, callback});
	}

	void MeshProvider::getMeshAsyn(BasicMeshType type, std::function<void(Mesh*)> callback, const std::string& texturePath)
	{
		BasicMeshAsset* basicMeshAsset = new BasicMeshAsset(type, texturePath);
		basicMeshAsset->load();
		m_map.push_back({ basicMeshAsset, callback });
	}

	void MeshProvider::tick(void* data)
	{
		for (auto it = m_map.begin(); it != m_map.end(); )
		{
			if (it->meshAsset->getLoadingState() == Asset::LoadingState::loading_state_succeeded)
			{
				it->callback(new Mesh(it->meshAsset));
				SAFE_DELETE_SET_NULL(it->meshAsset);
				it = m_map.erase(it);
			}
			else
			{
				it++;
			}	
		}
	}
}