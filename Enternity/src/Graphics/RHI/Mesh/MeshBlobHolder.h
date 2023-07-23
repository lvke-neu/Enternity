#pragma once
#include "Engine/BlobHolder.h"
#include "VertexDefine.h"

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
		const std::vector<Layout>& getLayout();
	private:
		MeshDesc m_meshDesc;
		std::vector<Layout> m_layout;
	};

	inline MeshBlobHolder::MeshDesc MeshBlobHolder::getMeshDesc()
	{
		return m_meshDesc;
	}

	inline const std::vector<Layout>& MeshBlobHolder::getLayout()
	{
		return m_layout;
	}
}