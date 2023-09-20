#include "Material.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Texture/Texture.h"

namespace Enternity
{
	Material::Material() : 
		m_ambientColor(Color::s_white),
		m_diffuseColor(Color::s_white),
		m_specularColor(Color::s_white),
		m_ambientTexturePath(""),
		m_diffuseTexturePath(""),
		m_specularTexturePath(""),
		m_ambientTexture(nullptr),
		m_diffuseTexture(nullptr),
		m_specularTexture(nullptr)
	{

	}

	Material::~Material()
	{
		SAFE_DELETE_SET_NULL(m_ambientTexture);
		SAFE_DELETE_SET_NULL(m_diffuseTexture);
		SAFE_DELETE_SET_NULL(m_specularTexture);
	}

	void Material::load()
	{
		Engine::GetInstance().getAssetLoader()->getAsset(m_ambientTexturePath.c_str(),
			[=](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(m_ambientTexture);
				m_ambientTexture = (Texture2D*)asset;
			});

		Engine::GetInstance().getAssetLoader()->getAsset(m_diffuseTexturePath.c_str(),
			[=](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(m_diffuseTexture);
				m_diffuseTexture = (Texture2D*)asset;
			});

		Engine::GetInstance().getAssetLoader()->getAsset(m_specularTexturePath.c_str(),
			[=](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(m_specularTexture);
				m_specularTexture = (Texture2D*)asset;
			});
	}

	void Material::bind(Renderer* renderer)
	{
		ENTERNITY_ASSERT(renderer);

		renderer->setVec4("u_ambientColor", m_ambientColor.toPointer());
		renderer->setVec4("u_diffuseColor", m_diffuseColor.toPointer());
		renderer->setVec4("u_specularColor", m_specularColor.toPointer());

		if (ASSET_LOAD_SUCCEED(m_ambientTexture))
		{
			m_ambientTexture->bind(0);
		}

		if (ASSET_LOAD_SUCCEED(m_diffuseTexture))
		{
			m_diffuseTexture->bind(1);
		}

		if (ASSET_LOAD_SUCCEED(m_specularTexture))
		{
			m_specularTexture->bind(2);
		}
	}

	void Material::unbind()
	{
		if (ASSET_LOAD_SUCCEED(m_ambientTexture))
		{
			m_ambientTexture->unbind(0);
		}

		if (ASSET_LOAD_SUCCEED(m_diffuseTexture))
		{
			m_diffuseTexture->unbind(1);
		}

		if (ASSET_LOAD_SUCCEED(m_specularTexture))
		{
			m_specularTexture->unbind(2);
		}
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<Material>("Material")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("ambientColor", &Material::get_ambientColor, &Material::set_ambientColor)
			.property("diffuseColor", &Material::get_diffuseColor, &Material::set_diffuseColor)
			.property("specularColor", &Material::get_specularColor, &Material::set_specularColor)
			.property("ambientTexturePath", &Material::get_ambientTexturePath, &Material::set_ambientTexturePath)
			.property("diffuseTexturePath", &Material::get_diffuseTexturePath, &Material::set_diffuseTexturePath)
			.property("specularTexturePath", &Material::get_specularTexturePath, &Material::set_specularTexturePath);
	}
}