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

	enum class LoadType
	{
		Sync,
		Asyn
	};

	class Blob;
	class BlobLoader
	{
	public:
		void load(Blob*& blob, const std::string& filePath, AssetType assetType, LoadType loadType);
	private:
		void loadGeneral(Blob*& blob, const std::string& filePath);
		void loadTexture(Blob*& blob, const std::string& filePath, int desired_channels = 0);
	};
}