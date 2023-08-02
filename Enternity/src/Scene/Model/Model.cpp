#include "Model.h"
#include "ModelBlobHolder.h"
#include "Animation.h"
#include "Animator.h"
#include "Graphics/RHI/Mesh/Mesh.h"
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
}