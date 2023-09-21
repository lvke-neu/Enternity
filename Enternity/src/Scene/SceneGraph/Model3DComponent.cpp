#include "Model3DComponent.h"
#include "Visual3D.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/Material.h"
#include "Graphics/Model/Model.h"
#include <glad/glad.h>

namespace Enternity
{
	static std::shared_ptr<Renderer> s_renderer = nullptr;

	Model3DComponent::Model3DComponent(Model* model)
	{
		ENTERNITY_ASSERT(model);

		ENTERNITY_ASSERT(model->m_meshs.size() == model->m_materials.size());
		ENTERNITY_ASSERT(model->m_meshs.size() == model->m_meshNames.size());
		ENTERNITY_ASSERT(model->m_materials.size() == model->m_materials.size());

		for (int i = 0; i < model->m_meshs.size(); i++)
		{
			m_visual3Ds.emplace_back(new Visual3D);
			m_visual3Ds.back()->set_mesh(std::shared_ptr<Mesh>(model->m_meshs[i]));
			m_visual3Ds.back()->set_material(std::shared_ptr<Material>(model->m_materials[i]));
			m_visual3Ds.back()->set_name(model->m_meshNames[i]);
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
		if (!m_enable)
		{
			return;
		}

		if (m_wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		for (auto& visual3D : m_visual3Ds)
		{
			visual3D->draw();
		}

		if (m_wireFrame)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void Model3DComponent::onAttachToNode(Node* node)
	{
		for (auto& visual3D : m_visual3Ds)
		{
			visual3D->set_node((Node3D*)node);
		}
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Model3DComponent>("Model3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("wireFrame", &Model3DComponent::get_wireFrame, &Model3DComponent::set_wireFrame)
			.property("visual3Ds", &Model3DComponent::get_visual3Ds, &Model3DComponent::set_visual3Ds);
	}
}