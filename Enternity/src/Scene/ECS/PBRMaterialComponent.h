#pragma once

namespace Enternity
{
	class Texture2D;
	struct PBRMaterialComponent
	{
		Texture2D* albedo{ nullptr };
		Texture2D* normal{ nullptr };
		Texture2D* metallic{ nullptr };
		Texture2D* roughness{ nullptr };
		Texture2D* ao{ nullptr };

		void load(const char* albedoTexturePath, const char* normalTexturePath, const char* metallicTexturePath, const char* roughnessTexturePath, const char* aoTexturePath);
		void unload();
	};
}