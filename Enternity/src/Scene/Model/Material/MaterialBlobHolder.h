#pragma once
#include "Engine/BlobHolder.h"
#include "MaterialDefine.h"
#include <vector>

namespace Enternity
{
	class MaterialBlobHolder : public BlobHolder
	{
		friend class Material;
		friend class MaterialBlobLoader;
	public:
		MaterialBlobHolder(BlobLoader* blobLoader, const std::string& path);
		virtual ~MaterialBlobHolder();
		virtual Asset* createAsset() override;
	private:
		std::vector<MaterialProperty> m_materialProperties;
	};
}