#include "Visual3DComponent.h"
#include "Node3D.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include <rttr/registration>
#include <glad/glad.h>

namespace Enternity
{
	Visual3DComponent::Visual3DComponent()
	{
		m_meshPath = "mesh://primitive=cube";
		m_rendererPath = "renderer://assets/shaders/visual3d/visual3d.rdr";
		m_texturePath = "texture://TEXTURE_2D?assets/textures/box_diffuse.png";

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

		Engine::GetInstance().getAssetLoader()->getAsset(m_texturePath.c_str(),
			[=](Asset* asset)
			{
				m_texture = (Texture2D*)asset;
			});
	}

	Visual3DComponent::~Visual3DComponent()
	{
		SAFE_DELETE_SET_NULL(m_mesh);
		SAFE_DELETE_SET_NULL(m_renderer);
		SAFE_DELETE_SET_NULL(m_texture);
	}

	void Visual3DComponent::command()
	{	
		if (!m_enable)
		{
			return;
		}

		if (ASSET_LOAD_SUCCEED(m_mesh) &&
			ASSET_LOAD_SUCCEED(m_renderer) &&
			ASSET_LOAD_SUCCEED(m_texture))
		{
			if (m_wireFrame)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			m_renderer->bind();
			m_renderer->setMat4("u_model", getNode<Node3D>()->getTransform().getWorldMatrix());
			m_texture->bind(0);
			m_mesh->draw();

			m_texture->unbind(0);
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
			.property("texturePath", &Visual3DComponent::get_texturePath, &Visual3DComponent::set_texturePath)
			.property("wireFrame", &Visual3DComponent::get_wireFrame, &Visual3DComponent::set_wireFrame);

	}
}