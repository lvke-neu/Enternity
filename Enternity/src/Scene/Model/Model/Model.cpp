#include "Model.h"
#include "ModelBlobHolder.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
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

		for (const auto& material : modelBlobHolder->m_materials)
		{
			Texture2D* m_ambientTexture = new Texture2D;
			Texture2D* m_diffuseTexture = new Texture2D;
			Texture2D* m_specularTexture = new Texture2D;

			m_ambientTexture->load((BlobHolder*)material.m_ambientTextureBlobHolder);
			m_diffuseTexture->load((BlobHolder*)material.m_diffuseTextureBlobHolder);
			m_specularTexture->load((BlobHolder*)material.m_specularTextureBlobHolder);

			m_materials.push_back({
					material.m_ambientColor,
					material.m_diffuseColor,
					material.m_specularColor,
					m_ambientTexture,
					m_diffuseTexture,
					m_specularTexture
				});		
		}

		m_path = modelBlobHolder->m_path;

		m_state = loading_state_succeeded;
	}

	void Model::unload()
	{
		for (auto& mesh : m_meshs)
		{
			SAFE_DELETE_SET_NULL(mesh);
		}
		m_meshs.clear();

		for (auto& materials : m_materials)
		{
			SAFE_DELETE_SET_NULL(materials.m_ambientTexture);
			SAFE_DELETE_SET_NULL(materials.m_diffuseTexture);
			SAFE_DELETE_SET_NULL(materials.m_specularTexture);
		}
		m_materials.clear();
	}

	void Model::draw(Renderer* renderer)
	{
		if (!renderer || !renderer->isLoadSucceeded())
		{
			return;
		}

		for (int i = 0; i < m_meshs.size(); i++)
		{
			renderer->setInt1("u_bUseTexture", m_bUseTexture);
			renderer->setVec4("u_ambientColor", m_materials[i].m_ambientColor);
			renderer->setVec4("u_diffuseColor", m_materials[i].m_diffuseColor);
			renderer->setVec4("u_specularColor", m_materials[i].m_specularColor);

			if (m_materials[i].m_ambientTexture->isLoadSucceeded())
			{
				m_materials[i].m_ambientTexture->bind(0);
			}

			if (m_materials[i].m_diffuseTexture->isLoadSucceeded())
			{
				m_materials[i].m_diffuseTexture->bind(1);
			}

			if (m_materials[i].m_specularTexture->isLoadSucceeded())
			{
				m_materials[i].m_specularTexture->bind(2);
			}
			
			m_meshs[i]->draw();

			if (m_materials[i].m_ambientTexture->isLoadSucceeded())
			{
				m_materials[i].m_ambientTexture->unbind(0);
			}

			if (m_materials[i].m_diffuseTexture->isLoadSucceeded())
			{
				m_materials[i].m_diffuseTexture->unbind(1);
			}

			if (m_materials[i].m_specularTexture->isLoadSucceeded())
			{
				m_materials[i].m_specularTexture->unbind(2);
			}	
		}
	}
}