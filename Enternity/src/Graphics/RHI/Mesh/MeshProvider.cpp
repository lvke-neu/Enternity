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

		if (meshAsset->getLoadingState() == Asset::loading_state_succeeded)
		{
			mesh = new Mesh(meshAsset);
		}

		SAFE_DELETE_SET_NULL(meshAsset);

		return mesh;
	}

	Mesh* MeshProvider::getMeshSync(BasicPrimitve type)
	{
		Mesh* mesh = nullptr;

		if (type == Quad)
		{
			QuadMeshAsset* quadMeshAsset = new QuadMeshAsset();
			quadMeshAsset->load(0);

			if (quadMeshAsset->getLoadingState() == Asset::loading_state_succeeded)
			{
				mesh = new Mesh(quadMeshAsset);
			}

			SAFE_DELETE_SET_NULL(quadMeshAsset);

			return mesh;
		}
		else if (type == Box)
		{
			BoxMeshAsset* boxMeshAsset = new BoxMeshAsset();
			boxMeshAsset->load(0);

			if (boxMeshAsset->getLoadingState() == Asset::loading_state_succeeded)
			{
				mesh = new Mesh(boxMeshAsset);
			}

			SAFE_DELETE_SET_NULL(boxMeshAsset);

			return mesh;
		}

		return mesh;
	}

	void MeshProvider::getMeshAsyn(const char* fullPath, std::function<void(Mesh*)> callback)
	{
		MeshAsset* meshAsset = new MeshAsset(fullPath);
		meshAsset->load();

		m_map.push_back({meshAsset, callback});
	}

	void MeshProvider::getMeshAsyn(BasicPrimitve type, std::function<void(Mesh*)> callback)
	{
		if (type == Quad)
		{
			QuadMeshAsset* quadMeshAsset = new QuadMeshAsset();
			quadMeshAsset->load();
			m_map.push_back({ quadMeshAsset, callback });
		}
		else if (type == Box)
		{
			BoxMeshAsset* boxMeshAsset = new BoxMeshAsset();
			boxMeshAsset->load();
			m_map.push_back({ boxMeshAsset, callback });
		}
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