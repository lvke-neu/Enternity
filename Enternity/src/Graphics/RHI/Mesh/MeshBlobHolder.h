#pragma once
#include "Engine/BlobHolder.h"

namespace Enternity
{
	class MeshBlobHolder : public BlobHolder
	{
		friend class MeshBlobLoader;
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
		MeshDesc getMeshDesc();
	private:
		MeshDesc m_meshDesc;
	};

	inline MeshBlobHolder::MeshDesc MeshBlobHolder::getMeshDesc()
	{
		return m_meshDesc;
	}
}