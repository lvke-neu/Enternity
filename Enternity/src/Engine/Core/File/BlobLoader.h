/***************************************************************************************
Author: lvke
Date:2023/2/5 22:50
Description:
BlobLoader
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <string>

namespace Enternity
{
	enum class AssetType
	{
		General,
		Model,
		Texture
	};

	class Blob;
	class BlobLoader
	{
	public:
		Blob* load(const std::string& filePath, AssetType assetType);
	private:
		Blob* loadGeneral(const std::string& filePath);
		Blob* loadTexture(const std::string& filePath, int desired_channels = 0);
	};
}