#include "MeshProvider.h"
#include "Mesh.h"
#include "MeshAsset.h"
#include "Common/Macro.h"

namespace Enternity
{
	Mesh* MeshProvider::getMesh(const char* fullPath)
	{
		MeshAsset* meshAsset = new MeshAsset(fullPath);
		meshAsset->load(0);

		Mesh* mesh = new Mesh(meshAsset);

		SAFE_DELETE_SET_NULL(meshAsset);

		return mesh;
	}
}