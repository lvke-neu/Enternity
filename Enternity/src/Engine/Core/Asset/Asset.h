/***************************************************************************************
Author: lvke
Date:2023/2/18 14:14
Description:
Asset
****************************************************************************************/
#pragma once
#include "AssetDefinition.h"


namespace Enternity
{
	const int AssetBlobNum = 10;

	class Blob;
	class Asset
	{
		friend class AssetLoader;
	public:
		Asset() = default;
		Asset(const AssetDescription& assetDesc);

		void load();

		std::string getAssetID();
		AssetType getAssetType();
		Blob** getBlob();
		AssetLoadState getAssetLoadState();

		void reset();
	protected:
		std::string m_assetID;
		AssetType m_assetType;
		AssetLoadType m_assetLoadType;
		Blob* m_blob[AssetBlobNum] = { nullptr };
		AssetLoadState m_assetLoadState;
	};
}