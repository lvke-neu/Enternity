#include "Visual3DComponent.h"
#include "Node3D.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/Material.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include <glad/glad.h>

namespace Enternity
{
	Visual3DComponent::Visual3DComponent()
	{
		m_meshPath = "mesh://primitive=cube";
		m_rendererPath = "renderer://assets/shaders/visual3d/visual3d.rdr";

		m_material = new Material;
		m_material->load();
		m_material->set_ambientTexturePath("texture://TEXTURE_2D?assets/textures/box_diffuse.png");
		m_material->set_diffuseTexturePath("texture://TEXTURE_2D?assets/textures/box_diffuse.png");
		m_material->set_specularTexturePath("texture://TEXTURE_2D?assets/textures/box_diffuse.png");
		

		Engine::GetInstance().getAssetLoader()->getAsset(m_meshPath.c_str(),
			[=](Asset* asset)
			{
				m_mesh = (Mesh*)asset;
			});

		Engine::GetInstance().getAssetLoader()->getAsset(m_rendererPath.c_str(),
			[=](Asset* asset)
			{
				m_renderer = (Renderer*)asset;
			});
	}

	Visual3DComponent::~Visual3DComponent()
	{
		SAFE_DELETE_SET_NULL(m_mesh);
		SAFE_DELETE_SET_NULL(m_renderer);
		SAFE_DELETE_SET_NULL(m_material);
	}

	void Visual3DComponent::command()
	{	
		if (!m_enable)
		{
			return;
		}

		if (ASSET_LOAD_SUCCEED(m_mesh) &&
			ASSET_LOAD_SUCCEED(m_renderer))
		{
			if (m_wireFrame)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			m_renderer->bind();
			m_renderer->setMat4("u_model", getNode<Node3D>()->getTransform().getWorldMatrix());
			
			if (ASSET_LOAD_SUCCEED(m_material->get_ambientTexture()))
			{
				m_material->get_ambientTexture()->bind(0);
			}

			m_mesh->draw();

			if (ASSET_LOAD_SUCCEED(m_material->get_ambientTexture()))
			{
				m_material->get_ambientTexture()->unbind(0);
			}
			m_renderer->unbind();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Visual3DComponent>("Visual3DComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("meshPath", &Visual3DComponent::get_meshPath, &Visual3DComponent::set_meshPath)
			.property("rendererPath", &Visual3DComponent::get_rendererPath, &Visual3DComponent::set_rendererPath)
			.property("wireFrame", &Visual3DComponent::get_wireFrame, &Visual3DComponent::set_wireFrame)
			.property("material", &Visual3DComponent::get_material, &Visual3DComponent::set_material);

	}
}