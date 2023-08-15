#include "ModelBlobHolder.h"
#include "Model.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Graphics/RHI/Texture/TextureBlobHolder.h"
#include "Common/Macro.h"

namespace Enternity
{
	ModelBlobHolder::ModelBlobHolder(BlobLoader* blobLoader, const std::string& path) :
		BlobHolder(blobLoader, path)
	{

	}

	ModelBlobHolder::~ModelBlobHolder()
	{
		for (auto& meshBlobHolder : m_meshBlobHolders)
		{
			SAFE_DELETE_SET_NULL(meshBlobHolder);
		}
		m_meshBlobHolders.clear();

		for (auto& material : m_materials)
		{
			SAFE_DELETE_SET_NULL(material.m_ambientTextureBlobHolder);
			SAFE_DELETE_SET_NULL(material.m_diffuseTextureBlobHolder);
			SAFE_DELETE_SET_NULL(material.m_specularTextureBlobHolder);
		}
		m_materials.clear();
	}

	Asset* ModelBlobHolder::createAsset()
	{
		return new Model;
	}
}