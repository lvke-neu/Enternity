#pragma once
#include "Engine/BlobHolder.h"
#include <vector>

namespace Enternity
{
	class ModelBlobHolder : public BlobHolder
	{
		friend class ModelBlobLoader;
	public:
		struct SubMeshDesc
		{
			unsigned int vertexDataOffset;
			unsigned int vertexDataSize;
			unsigned int indexDataOffset;
			unsigned int indexDataSize;
		};
	public:
		ModelBlobHolder(BlobLoader* blobLoader, const std::string& path);
		const std::vector<SubMeshDesc>& getSubMeshDescs() const;
		virtual Asset* createAsset() override;
	private:
		std::vector<SubMeshDesc> m_subMeshDescs;
	};

	inline const std::vector<ModelBlobHolder::SubMeshDesc>& ModelBlobHolder::getSubMeshDescs() const
	{
		return m_subMeshDescs;
	}
}