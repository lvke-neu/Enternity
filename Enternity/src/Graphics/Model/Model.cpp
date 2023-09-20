#include "Model.h"
#include "ModelBlobHolder.h"
#include "Graphics/Material.h"
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
				continue;
			}
			m_meshs.push_back(mesh);
		}

		m_materials = modelBlobHolder->m_materials;
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
			SAFE_DELETE_SET_NULL(materials);
		}
		m_materials.clear();
	}
}