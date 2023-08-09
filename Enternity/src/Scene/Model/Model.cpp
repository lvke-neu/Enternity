#include "Model.h"
#include "ModelBlobHolder.h"
#include "Animation.h"
#include "Animator.h"
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
				m_state = loading_state_failed;
				return;
			}
			m_meshs.push_back(mesh);
		}

		for (auto texture2DBlobHolder : modelBlobHolder->m_texture2DBlobHolders)
		{
			Texture2D* texture2D = new Texture2D;
			texture2D->load((BlobHolder*)texture2DBlobHolder);
			if (!texture2D->isLoadSucceeded())
			{
				SAFE_DELETE_SET_NULL(texture2D);
				//m_state = loading_state_failed;
			}
			m_materials.push_back(texture2D);
		}

		m_animation = modelBlobHolder->m_animation->clone();
		m_animator = new Animator(m_animation);

		m_path = modelBlobHolder->getPath();
		m_state = loading_state_succeeded;
	}

	void Model::unload()
	{
		for (auto& mesh : m_meshs)
		{
			SAFE_DELETE_SET_NULL(mesh);
		}
		m_meshs.clear();

		for (auto& texture2D : m_materials)
		{
			SAFE_DELETE_SET_NULL(texture2D);
		}
		m_materials.clear();

		SAFE_DELETE_SET_NULL(m_animation);
		SAFE_DELETE_SET_NULL(m_animator);
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

	void Model::draw2()
	{
		for (int i = 0; i < m_meshs.size(); i++)
		{
			if (m_meshs[i])
			{
				m_materials[i]->bind(0);
				m_meshs[i]->draw();
			}
		}
	}
}