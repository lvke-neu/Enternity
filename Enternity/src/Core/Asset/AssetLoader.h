#pragma once

namespace Enternity
{
	enum class AssetType
	{
		Shader
	};

	class Blob;
	class AssetLoader
	{
	public:
		Blob* load(const char* assetPath, AssetType type);
	private:
		Blob* loadShaderImpl(const char* assetPath);
	};
}