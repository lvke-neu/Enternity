/***************************************************************************************
Author: lvke
Date:2023/2/18 14:14
Description:
Asset
****************************************************************************************/
#pragma once
#include <string>

namespace Enternity
{
	const int AssetBlobNum = 10;

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
		loading
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

	class Blob;
	class Asset
	{
		friend class AssetLoader;
	public:
		Asset(const AssetDescription& assetDesc);

		std::string getAssetID();
		AssetType getAssetType();
		Blob** getBlob();
		AssetLoadState getAssetLoadState();

		void load();
	protected:
		std::string m_assetID;
		AssetType m_assetType;
		AssetLoadType m_assetLoadType;
		Blob* m_blob[AssetBlobNum] = { nullptr };
		AssetLoadState m_assetLoadState;
	};
}