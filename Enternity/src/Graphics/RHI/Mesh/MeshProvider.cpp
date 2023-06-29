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

	void MeshProvider::getMeshAsyn(const char* fullPath, std::function<void(Mesh*)> callback)
	{
		MeshAsset* meshAsset = new MeshAsset(fullPath);
		meshAsset->load();

		m_map.push_back({meshAsset, callback});
	}

	Mesh* MeshProvider::getQuadMesh()
	{
		Mesh* mesh = nullptr;

		QuadMeshAsset* quadMeshAsset = new QuadMeshAsset();
		quadMeshAsset->load(0);

		if (quadMeshAsset->getLoadingState() == Asset::loading_state_succeeded)
		{
			mesh = new Mesh(quadMeshAsset);
		}

		SAFE_DELETE_SET_NULL(quadMeshAsset);

		return mesh;
	}

	Mesh* MeshProvider::getBoxMesh()
	{
		Mesh* mesh = nullptr;

		BoxMeshAsset* boxMeshAsset = new BoxMeshAsset();
		boxMeshAsset->load(0);

		if (boxMeshAsset->getLoadingState() == Asset::loading_state_succeeded)
		{
			mesh = new Mesh(boxMeshAsset);
		}

		SAFE_DELETE_SET_NULL(boxMeshAsset);

		return mesh;
	}

	void MeshProvider::tick(void* data)
	{
		for (auto it = m_map.begin(); it != m_map.end(); )
		{
			if (it->meshAsset->getLoadingState() == Asset::loading_state_succeeded)
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