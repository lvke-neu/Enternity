#include "Model.h"
#include "ModelBlobHolder.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Scene/Model/Material/Material.h"
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

		m_state = loading_state_succeeded;
	}

	void Model::unload()
	{
		for (auto& mesh : m_meshs)
		{
			SAFE_DELETE_SET_NULL(mesh);
		}
		m_meshs.clear();
	}

	void Model::draw(Renderer* renderer, Material* material)
	{
		for (int i = 0; i < m_meshs.size(); i++)
		{
			if (material && material->isLoadSucceeded())
			{
				renderer->setVec4("u_ambientColor", material->m_materialPropertyImpls[i].m_ambientColor);
				renderer->setVec4("u_diffuseColor", material->m_materialPropertyImpls[i].m_diffuseColor);
				renderer->setVec4("u_specularColor", material->m_materialPropertyImpls[i].m_specularColor);

				if (material->m_materialPropertyImpls[i].m_ambientTexture->isLoadSucceeded())
				{
					material->m_materialPropertyImpls[i].m_ambientTexture->bind(0);
				}

				if (material->m_materialPropertyImpls[i].m_diffuseTexture->isLoadSucceeded())
				{
					material->m_materialPropertyImpls[i].m_diffuseTexture->bind(1);
				}

				if (material->m_materialPropertyImpls[i].m_specularTexture->isLoadSucceeded())
				{
					material->m_materialPropertyImpls[i].m_specularTexture->bind(2);
				}
			}

			m_meshs[i]->draw();

			if (material && material->isLoadSucceeded())
			{
				if (material->m_materialPropertyImpls[i].m_ambientTexture->isLoadSucceeded())
				{
					material->m_materialPropertyImpls[i].m_ambientTexture->unbind(0);
				}

				if (material->m_materialPropertyImpls[i].m_diffuseTexture->isLoadSucceeded())
				{
					material->m_materialPropertyImpls[i].m_diffuseTexture->unbind(1);
				}

				if (material->m_materialPropertyImpls[i].m_specularTexture->isLoadSucceeded())
				{
					material->m_materialPropertyImpls[i].m_specularTexture->unbind(2);
				}
			}
		}

		for (auto& mesh : m_meshs)
		{
			if (mesh)
			{

				mesh->draw();
			}
		}
	}
}