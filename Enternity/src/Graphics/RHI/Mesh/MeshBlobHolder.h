#pragma once
#include "Engine/BlobHolder.h"
#include "VertexDefine.h"

namespace Enternity
{
	class MeshBlobHolder : public BlobHolder
	{
		friend class Mesh;
		friend class MeshBlobLoader;
		friend class ModelBlobLoader;
	public:
		struct MeshDesc
		{
			unsigned int vertexDataOffset;
			unsigned int vertexDataSize;
			unsigned int indexDataOffset;
			unsigned int indexDataSize;
		};
	public:
		MeshBlobHolder(BlobLoader* blobLoader, const std::string& path);
		virtual Asset* createAsset() override;
	private:
		MeshDesc m_meshDesc;
		std::vector<Layout> m_layout;
	};
}