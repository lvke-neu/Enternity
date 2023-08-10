#include "ModelBlobHolder.h"
#include "Graphics/RHI/Mesh/MeshBlobHolder.h"
#include "Graphics/RHI/Texture/TextureBlobHolder.h"
#include "Model.h"
#include "Animation.h"
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

		for (auto& texture2DBlobHolder : m_texture2DBlobHolders)
		{
			SAFE_DELETE_SET_NULL(texture2DBlobHolder);
		}
		m_texture2DBlobHolders.clear();


		for (auto& animation : m_animations)
		{
			SAFE_DELETE_SET_NULL(animation);
		}
		m_animations.clear();
	}

	Asset* ModelBlobHolder::createAsset()
	{
		return new Model;
	}
}