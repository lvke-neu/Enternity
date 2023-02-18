#include "Asset.h"
#include "AssetLoader.h"

namespace Enternity
{
	Asset::Asset(const AssetDescription& assetDesc) :
		m_assetID(assetDesc.assetID), 
		m_assetType(assetDesc.assetType),
		m_assetLoadType(assetDesc.assetLoadType),
		m_assetLoadState(AssetLoadState::loading)
	{
	
	}

	std::string Asset::getAssetID()
	{
		return m_assetID;
	}

	AssetType Asset::getAssetType()
	{
		return m_assetType;
	}

	Blob** Asset::getBlob()
	{
		return m_blob;
	}

	AssetLoadState Asset::getAssetLoadState()
	{
		return m_assetLoadState;
	}

	void Asset::load()
	{
		AssetLoader assetLoader;
		assetLoader.loadAsset(this);
	}
}