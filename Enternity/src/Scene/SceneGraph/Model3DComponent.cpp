#include "Model3DComponent.h"
#include "Visual3DComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/Model/Model.h"

namespace Enternity
{
	Model3DComponent::Model3DComponent(Model* model)
	{
		ENTERNITY_ASSERT(model);

		ENTERNITY_ASSERT(model->m_meshs.size() == model->m_materials.size());

		for (int i = 0; i < model->m_meshs.size(); i++)
		{
			m_visual3DComponents.emplace_back(new Visual3DComponent);
			m_visual3DComponents.back()->set_mesh(model->m_meshs[i]);
			m_visual3DComponents.back()->set_material(model->m_materials[i]);
		}

		for (auto& visual3DComponent : m_visual3DComponents)
		{
			visual3DComponent->set_renderer((Renderer*)Engine::GetInstance().getAssetLoader()->getAsset("renderer://assets/shaders/model/model.rdr"));
		}
	}

	Model3DComponent::~Model3DComponent()
	{
		for (auto& visual3DComponent : m_visual3DComponents)
		{
			SAFE_DELETE_SET_NULL(visual3DComponent);
		}
	}

	void Model3DComponent::onAttachToNode(Node* node)
	{
		for (auto& visual3DComponent : m_visual3DComponents)
		{
			visual3DComponent->addToNode(node);
		}
	}
}