/***************************************************************************************
Author: lvke
Date:2023/2/20 21:10
Description:
AssetDefinition
****************************************************************************************/
#pragma once
#include <string>

namespace Enternity
{
	enum class AssetType
	{
		Shader,
		Texture,
		Mesh
	};

	enum class AssetLoadState
	{
		success,
		failure,
		unloaded
	};

	enum class AssetLoadType
	{
		Sync,
		Asyn
	};


	struct AssetDescription
	{
		std::string assetID;
		AssetType assetType;
		AssetLoadType assetLoadType;
	};

}