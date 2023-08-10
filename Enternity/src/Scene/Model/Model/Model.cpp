#include "Model.h"
#include "ModelBlobHolder.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	Model::~Model()
	{
		unload();
	}

	void Model::load(BlobHolder* blobHolder)
	{
		ModelBlobHolder* modelBlobHolder = dynamic_cast<ModelBlobHolder*>(blobHolder);
		if (!modelBlobHolder || !modelBlobHolder->isLoadSucceeded())
		{
			m_state = loading_state_failed;
			return;
		}

		for (auto meshBlobHolder : modelBlobHolder->m_meshBlobHolders)
		{
			Mesh* mesh = new Mesh;
			mesh->load((BlobHolder*)meshBlobHolder);
			if (!mesh->isLoadSucceeded())
			{
				SAFE_DELETE_SET_NULL(mesh);
				continue;
			}
			m_meshs.push_back(mesh);
		}

		for (const auto& materialBlobHolder : modelBlobHolder->m_materialBlobHolders)
		{
			Texture2D* m_ambientTexture = new Texture2D;
			Texture2D* m_diffuseTexture = new Texture2D;
			Texture2D* m_specularTexture = new Texture2D;

			m_ambientTexture->load((BlobHolder*)materialBlobHolder.m_ambientTextureBlobHolder);
			m_diffuseTexture->load((BlobHolder*)materialBlobHolder.m_diffuseTextureBlobHolder);
			m_specularTexture->load((BlobHolder*)materialBlobHolder.m_specularTextureBlobHolder);

			m_materials.push_back(
				{ 
					materialBlobHolder.m_ambientColor, 
					materialBlobHolder.m_diffuseColor, 
					materialBlobHolder.m_specularColor,
					m_ambientTexture,
					m_diffuseTexture,
					m_specularTexture
				});
		}

		m_state = loading_state_succeeded;
	}

	void Model::unload()
	{
		for (auto& mesh : m_meshs)
		{
			SAFE_DELETE_SET_NULL(mesh);
		}
		m_meshs.clear();

		for (auto& material : m_materials)
		{
			SAFE_DELETE_SET_NULL(material.m_ambientTexture);
			SAFE_DELETE_SET_NULL(material.m_diffuseTexture);
			SAFE_DELETE_SET_NULL(material.m_specularTexture);
		}
		m_materials.clear();
	}

	void Model::draw()
	{
		for (auto& mesh : m_meshs)
		{
			if (mesh)
			{
				mesh->draw();
			}
		}
	}
}