/***************************************************************************************
Author: lvke
Date:2023/2/18 14:14
Description:
Asset: data store in m_blob or m_meshs or......
****************************************************************************************/
#pragma once
#include "AssetDefinition.h"

namespace Enternity
{
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
		Blob* getBlob();
		std::vector<Mesh>& getMeshs();
		AssetLoadState getAssetLoadState();

		void reset();
	protected:
		std::string m_assetID;
		AssetType m_assetType;
		AssetLoadType m_assetLoadType;
		Blob* m_blob{ nullptr };
		std::vector<Mesh> m_meshs;
		AssetLoadState m_assetLoadState;
	};
}