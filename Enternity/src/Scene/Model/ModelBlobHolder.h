#pragma once
#include "Engine/BlobHolder.h"
#include "Graphics/RHI/Mesh/VertexDefine.h"
#include <vector>
#include <string>
#include <map>

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
		std::map<std::string, BoneInfo> m_boneInfoMap;
		int m_boneCounter = 0;
	};
}