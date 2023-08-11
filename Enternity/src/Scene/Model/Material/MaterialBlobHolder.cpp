#include "MaterialBlobHolder.h"
#include "Material.h"
#include "Graphics/RHI/Texture/TextureBlobHolder.h"
#include "Common/Macro.h"

namespace Enternity
{
	MaterialBlobHolder::MaterialBlobHolder(BlobLoader* blobLoader, const std::string& path) :
		BlobHolder(blobLoader, path)
	{

	}

	MaterialBlobHolder::~MaterialBlobHolder()
	{
		for (auto& materialProperty : m_materialProperties)
		{
			SAFE_DELETE_SET_NULL(materialProperty.m_ambientTextureBlobHolder);
			SAFE_DELETE_SET_NULL(materialProperty.m_diffuseTextureBlobHolder);
			SAFE_DELETE_SET_NULL(materialProperty.m_specularTextureBlobHolder);
		}
		m_materialProperties.clear();
	}

	Asset* MaterialBlobHolder::createAsset()
	{
		return new Material;
	}
}