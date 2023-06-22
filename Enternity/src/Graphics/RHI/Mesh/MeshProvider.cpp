#include "MeshProvider.h"
#include "Mesh.h"
#include "MeshAsset.h"
#include "Common/Macro.h"

namespace Enternity
{
	Mesh* MeshProvider::getMesh(const char* fullPath)
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
}