#include "SkyBoxComponent.h"
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
	SkyBoxComponent::SkyBoxComponent()
	{
		m_skyboxType = Type::HDR;
		m_meshPath = "mesh://primitive=cube";
		m_rendererPath = "renderer://assets/shaders/skybox/skybox.rdr";
		m_textureCubeMapHDRPath = "texture://CUBE_MAP_HDR?assets/textures/hdr/evening_meadow_4k.hdr";
		m_textureCubeMapPath = "texture://CUBE_MAP?assets/textures/skybox/daylight/.png";

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
		Engine::GetInstance().getAssetLoader()->getAsset(m_textureCubeMapHDRPath.c_str(),
			[=](Asset* asset)
			{
				m_textureCubeMapHDR = (TextureCubeMapHDR*)asset;
			});
		Engine::GetInstance().getAssetLoader()->getAsset(m_textureCubeMapPath.c_str(),
			[=](Asset* asset)
			{
				m_textureCubeMap = (TextureCubeMap*)asset;
			});
	}

	SkyBoxComponent::~SkyBoxComponent()
	{
		SAFE_DELETE_SET_NULL(m_mesh);
		SAFE_DELETE_SET_NULL(m_renderer);
		SAFE_DELETE_SET_NULL(m_textureCubeMapHDR);
		SAFE_DELETE_SET_NULL(m_textureCubeMap);
	}

	void SkyBoxComponent::command()
	{
		if (!m_enable)
		{
			return;
		}

		if (ASSET_LOAD_SUCCEED(m_mesh) &&
			ASSET_LOAD_SUCCEED(m_renderer) &&
			ASSET_LOAD_SUCCEED(m_textureCubeMapHDR) &&
			ASSET_LOAD_SUCCEED(m_textureCubeMap))
		{

			glDepthFunc(GL_LEQUAL);
			m_renderer->bind();
			if (m_skyboxType == Type::HDR)
			{
				m_textureCubeMapHDR->bind(0);
				m_renderer->setInt1("type", 0);
			}
			else if (m_skyboxType == Type::Image)
			{
				m_renderer->setInt1("type", 1);
				m_textureCubeMap->bind(0);
			}
			m_mesh->draw();

			m_textureCubeMapHDR->unbind(0);
			m_textureCubeMap->unbind(0);
			m_renderer->unbind();
			glDepthFunc(GL_LESS);
		}
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<SkyBoxComponent>("SkyBoxComponent")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("meshPath", &SkyBoxComponent::get_meshPath, &SkyBoxComponent::set_meshPath)
			.property("rendererPath", &SkyBoxComponent::get_rendererPath, &SkyBoxComponent::set_rendererPath)
			.property("textureCubeMapHDRPath", &SkyBoxComponent::get_textureCubeMapHDRPath, &SkyBoxComponent::set_textureCubeMapHDRPath)
			.property("textureCubeMapPath", &SkyBoxComponent::get_textureCubeMapPath, &SkyBoxComponent::set_textureCubeMapPath)
			.property("skyboxType", &SkyBoxComponent::get_skyboxType, &SkyBoxComponent::set_skyboxType);
	
		rttr::registration::enumeration<SkyBoxComponent::Type>("SkyBoxComponent::Type")
		(
			rttr::detail::enum_data("HDR", SkyBoxComponent::Type::HDR),
			rttr::detail::enum_data("Image", SkyBoxComponent::Type::Image)
		);
	}
}