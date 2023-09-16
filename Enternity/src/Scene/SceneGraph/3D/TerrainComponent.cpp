#include "TerrainComponent.h"
#include "Node3D.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoader.h"
#include "Engine/BlobLoaderManager.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Scene/Model/ModelBlobHolder.h"
#include "Scene/Model/Model.h"
#include <glad/glad.h>


namespace Enternity
{
	TerrainComponent::TerrainComponent()
	{
		m_meshPath = "model://assets/models/quad2.obj";
		m_rendererPath = "renderer://assets/shaders/terrain/terrain.rdr";
		m_texturePath = "texture://TEXTURE_2D?assets/textures/terrain/rock2.jpg";

		Engine::GetInstance().getAssetLoader()->getAsset(m_meshPath.c_str(),
			[=](Asset* asset)
			{
				m_mesh = ((Model*)asset)->get_meshs()[0];
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

	TerrainComponent::~TerrainComponent()
	{
		SAFE_DELETE_SET_NULL(m_mesh);
		SAFE_DELETE_SET_NULL(m_renderer);
		SAFE_DELETE_SET_NULL(m_texture);
	}

	void TerrainComponent::tick()
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
		rttr::registration::class_<TerrainComponent>("TerrainComponent")
			.constructor<>()(rttr::policy::ctor::as_raw_ptr)
			.property("meshPath", &TerrainComponent::get_meshPath, &TerrainComponent::set_meshPath)
			.property("rendererPath", &TerrainComponent::get_rendererPath, &TerrainComponent::set_rendererPath)
			.property("wireFrame", &TerrainComponent::get_wireFrame, &TerrainComponent::set_wireFrame);
	}
}