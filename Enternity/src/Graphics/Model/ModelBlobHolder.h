#pragma once
#include "Engine/BlobHolder.h"
#include <vector>

namespace Enternity
{	
	class MeshBlobHolder;
	class Material;
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
		std::vector<Material*> m_materials;//not delete when deconstructor, Assign to model
		std::vector<std::string> m_meshNames;
	};
}