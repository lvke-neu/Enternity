#include "PBRMaterialComponent.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"

namespace Enternity
{
	void PBRMaterialComponent::load(const char* albedoTexturePath, const char* normalTexturePath, const char* metallicTexturePath, const char* roughnessTexturePath, const char* aoTexturePath)
	{
		Engine::GetInstance().getAssetLoader()->getAsset(albedoTexturePath,
			[&](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(albedo);
				albedo = dynamic_cast<Texture2D*>(asset);
			});

		Engine::GetInstance().getAssetLoader()->getAsset(normalTexturePath,
			[&](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(normal);
				normal = dynamic_cast<Texture2D*>(asset);
			});

		Engine::GetInstance().getAssetLoader()->getAsset(metallicTexturePath,
			[&](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(metallic);
				metallic = dynamic_cast<Texture2D*>(asset);
			});

		Engine::GetInstance().getAssetLoader()->getAsset(roughnessTexturePath,
			[&](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(roughness);
				roughness = dynamic_cast<Texture2D*>(asset);
			});

		Engine::GetInstance().getAssetLoader()->getAsset(aoTexturePath,
			[&](Asset* asset)
			{
				SAFE_DELETE_SET_NULL(ao);
				ao = dynamic_cast<Texture2D*>(asset);
			});
	}

	void PBRMaterialComponent::unload()
	{
		SAFE_DELETE_SET_NULL(albedo);
		SAFE_DELETE_SET_NULL(normal);
		SAFE_DELETE_SET_NULL(metallic);
		SAFE_DELETE_SET_NULL(roughness);
		SAFE_DELETE_SET_NULL(ao);
	}
}