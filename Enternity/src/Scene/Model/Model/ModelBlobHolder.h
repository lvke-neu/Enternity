#pragma once
#include "Engine/BlobHolder.h"
#include "Material.h"
#include <vector>

namespace Enternity
{	
	class MeshBlobHolder;
	class ModelBlobHolder : public BlobHolder
	{
		friend class Model;
		friend class ModelBlobLoader;
	public:
		ModelBlobHolder(BlobLoader* blobLoader, const std::string& path);
		virtual ~ModelBlobHolder();
		virtual Asset* createAsset() override;
	private:
		std::vector<MeshBlobHolder*> m_meshBlobHolders;
		std::vector<MaterialBlobHolder> m_materialBlobHolders;
	};
}