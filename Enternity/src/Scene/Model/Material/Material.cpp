#include "Material.h"
#include "MaterialBlobHolder.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	Material::~Material()
	{
		unload();
	}

	void Material::load(BlobHolder* blobHolder)
	{
		MaterialBlobHolder* materialBlobHolder = dynamic_cast<MaterialBlobHolder*>(blobHolder);
		if (!materialBlobHolder || !materialBlobHolder->isLoadSucceeded())
		{
			m_state = loading_state_failed;
			return;
		}

		for (const auto& materialProperty : materialBlobHolder->m_materialProperties)
		{
			Texture2D* m_ambientTexture = new Texture2D;
			Texture2D* m_diffuseTexture = new Texture2D;
			Texture2D* m_specularTexture = new Texture2D;

			m_ambientTexture->load((BlobHolder*)materialProperty.m_ambientTextureBlobHolder);
			m_diffuseTexture->load((BlobHolder*)materialProperty.m_diffuseTextureBlobHolder);
			m_specularTexture->load((BlobHolder*)materialProperty.m_specularTextureBlobHolder);

			m_materialPropertyImpls.push_back({
					materialProperty.m_ambientColor,
					materialProperty.m_diffuseColor,
					materialProperty.m_specularColor,
					m_ambientTexture,
					m_diffuseTexture,
					m_specularTexture
				});		
		}

		m_state = loading_state_succeeded;
	}

	void Material::unload()
	{
		for (auto& materialPropertyImpl : m_materialPropertyImpls)
		{
			SAFE_DELETE_SET_NULL(materialPropertyImpl.m_ambientTexture);
			SAFE_DELETE_SET_NULL(materialPropertyImpl.m_diffuseTexture);
			SAFE_DELETE_SET_NULL(materialPropertyImpl.m_specularTexture);
		}
		m_materialPropertyImpls.clear();
	}
}