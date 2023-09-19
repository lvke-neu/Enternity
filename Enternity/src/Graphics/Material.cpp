#include "Material.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
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