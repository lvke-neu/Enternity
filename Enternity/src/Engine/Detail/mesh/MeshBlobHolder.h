#pragma once
#include "Engine/BlobHolder.h"
#include <vector>

namespace Enternity
{
	class MeshBlobHolder : public BlobHolder
	{
	public:
		MeshBlobHolder(BlobLoader* blobLoader, const std::string& path);
	private:
		struct SubMesh
		{
			unsigned int vertexDataOffset;
			unsigned int vertexDataSize;
			unsigned int indexDataOffset;
			unsigned int indexDataSize;
		};
		std::vector<SubMesh> m_subMeshDesc;
	};
}