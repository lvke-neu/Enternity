#pragma once

namespace Enternity
{
	enum class AssetType
	{
		Shader,
		Texture
	};

	class Blob;
	class AssetLoader
	{
	public:
		Blob* load(const char* assetPath, AssetType type, int flip = 1);
	private:
		Blob* loadShaderImpl(const char* assetPath);
		Blob* loadTextureImpl(const char* assetPath, int flip = 1);
	};
}