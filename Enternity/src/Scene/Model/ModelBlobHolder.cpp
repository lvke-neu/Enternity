#include "ModelBlobHolder.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Model.h"
#include "Common/Macro.h"

namespace Enternity
{
	ModelBlobHolder::ModelBlobHolder(BlobLoader* blobLoader, const std::string& path) :
		BlobHolder(blobLoader, path)
	{

	}

	ModelBlobHolder::~ModelBlobHolder()
	{
		for (auto& meshBlobHolder : m_meshBlobHolders)
		{
			SAFE_DELETE_SET_NULL(meshBlobHolder);
		}
		m_meshBlobHolders.clear();
	}

	Asset* ModelBlobHolder::createAsset()
	{
		return new Model;
	}
}