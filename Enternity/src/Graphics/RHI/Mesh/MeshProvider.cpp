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
		Engine::GetInstance().getEventSystem()->registerEvent(EventType::Tick, BIND(MeshProvider::tick));
	}

	MeshProvider::~MeshProvider()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::Tick, BIND(MeshProvider::tick));
	}

	Mesh* MeshProvider::getMeshSync(const char* fullPath)
	{
		Mesh* mesh = nullptr;

		MeshAsset* meshAsset = new MeshAsset(fullPath);
		meshAsset->load(0);

		if (meshAsset->getLoadingState() == Asset::loading_state_succeeded)
		{
			mesh = new Mesh(meshAsset);
		}

		SAFE_DELETE_SET_NULL(meshAsset);

		return mesh;
	}

	void MeshProvider::getMeshAsyn(Mesh** mesh, const char* fullPath, std::function<void(void)> callback)
	{
		MeshAsset* meshAsset = new MeshAsset(fullPath);
		meshAsset->load();

		m_map.insert({ mesh, {meshAsset, callback} });
	}

	void MeshProvider::tick(void* data)
	{
		for (auto it = m_map.begin(); it != m_map.end(); )
		{
			if (it->second.meshAsset->getLoadingState() == Asset::loading_state_succeeded)
			{
				*it->first = new Mesh(it->second.meshAsset);
				SAFE_DELETE_SET_NULL(it->second.meshAsset);
				it->second.callback();
				it = m_map.erase(it);
			}
			else
			{
				it++;
			}	
		}
	}
}