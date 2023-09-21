#include "Model3DComponent.h"
#include "Visual3D.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Model/Model.h"

namespace Enternity
{
	static std::shared_ptr<Renderer> s_renderer = nullptr;

	Model3DComponent::Model3DComponent(Model* model)
	{
		ENTERNITY_ASSERT(model);

		ENTERNITY_ASSERT(model->m_meshs.size() == model->m_materials.size());

		for (int i = 0; i < model->m_meshs.size(); i++)
		{
			m_visual3Ds.emplace_back(new Visual3D);
			m_visual3Ds.back()->set_mesh(std::shared_ptr<Mesh>(model->m_meshs[i]));
			m_visual3Ds.back()->set_material(std::shared_ptr<Material>(model->m_materials[i]));
		}

		if (!s_renderer)
		{
			s_renderer = std::shared_ptr<Renderer>((Renderer*)Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/model/model.rdr"));
		}

		for (auto& visual3D : m_visual3Ds)
		{
			visual3D->set_renderer(s_renderer);
		}
	}

	Model3DComponent::~Model3DComponent()
	{
		for (auto& visual3D : m_visual3Ds)
		{
			SAFE_DELETE_SET_NULL(visual3D);
		}
	}

	void Model3DComponent::command()
	{
		for (auto& visual3D : m_visual3Ds)
		{
			visual3D->draw();
		}
	}

	void Model3DComponent::onAttachToNode(Node* node)
	{
		for (auto& visual3D : m_visual3Ds)
		{
			visual3D->set_node((Node3D*)node);
		}
	}
}