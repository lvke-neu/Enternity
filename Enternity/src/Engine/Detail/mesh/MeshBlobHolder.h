#pragma once
#include "Engine/BlobHolder.h"
#include <vector>

namespace Enternity
{
	class MeshBlobHolder : public BlobHolder
	{
		friend class MeshBlobLoader;
	public:
		struct SubMeshDesc
		{
			unsigned int vertexDataOffset;
			unsigned int vertexDataSize;
			unsigned int indexDataOffset;
			unsigned int indexDataSize;
		};
	public:
		MeshBlobHolder(BlobLoader* blobLoader, const std::string& path);
		const std::vector<SubMeshDesc>& getSubMeshDescs() const;
	private:
		std::vector<SubMeshDesc> m_subMeshDescs;
	};

	inline const std::vector<MeshBlobHolder::SubMeshDesc>& MeshBlobHolder::getSubMeshDescs() const
	{
		return m_subMeshDescs;
	}
}