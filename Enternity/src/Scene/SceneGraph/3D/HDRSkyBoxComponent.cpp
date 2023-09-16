#include "HDRSkyBoxComponent.h"
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
	HDRSkyBoxComponent::HDRSkyBoxComponent()
	{
		m_meshPath = "mesh://primitive=cube";
		m_rendererPath = "renderer://assets/shaders/skybox/skybox.rdr";
		m_texturePath = "texture://CUBE_MAP_HDR?assets/textures/hdr/newport_loft.hdr";

		m_mesh = (Mesh*)Engine::GetInstance().getAssetLoader()->getAsset(m_meshPath.c_str());
		m_renderer = (Renderer*)Engine::GetInstance().getAssetLoader()->getAsset(m_rendererPath.c_str());
		m_texture = (TextureCubeMapHDR*)Engine::GetInstance().getAssetLoader()->getAsset(m_texturePath.c_str());
	}

	HDRSkyBoxComponent::~HDRSkyBoxComponent()
	{
		SAFE_DELETE_SET_NULL(m_mesh);
		SAFE_DELETE_SET_NULL(m_renderer);
		SAFE_DELETE_SET_NULL(m_texture);
	}

	void HDRSkyBoxComponent::tick()
	{
		if (!m_enable)
		{
			return;
		}

		glDepthFunc(GL_LEQUAL);
		m_renderer->bind();
		m_texture->bind(0);
		m_mesh->draw();
		m_texture->unbind(0);
		m_renderer->unbind();
		glDepthFunc(GL_LESS);
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<HDRSkyBoxComponent>("HDRSkyBoxComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("meshPath", &HDRSkyBoxComponent::get_meshPath, &HDRSkyBoxComponent::set_meshPath)
			.property("rendererPath", &HDRSkyBoxComponent::get_rendererPath, &HDRSkyBoxComponent::set_rendererPath)
			.property("texturePath", &HDRSkyBoxComponent::get_texturePath, &HDRSkyBoxComponent::set_texturePath);

	}
}