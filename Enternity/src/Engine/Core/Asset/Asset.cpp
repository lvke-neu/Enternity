#include "Asset.h"
#include "Core/Basic/Macro.h"
#include "Core/Memory/Blob.h"
#include "Core/Asset/AssetLoader.h"

namespace Enternity
{
	Asset::Asset(const AssetDescription& assetDesc) :
		m_assetID(assetDesc.assetID), 
		m_assetType(assetDesc.assetType),
		m_assetLoadType(assetDesc.assetLoadType),
		m_assetLoadState(AssetLoadState::Unloaded)
	{
	
	}

	void Asset::load()
	{
		AssetLoader assetLoader;
		assetLoader.loadAsset(*this);
	}

	std::string Asset::getAssetID()
	{
		return m_assetID;
	}

	AssetType Asset::getAssetType()
	{
		return m_assetType;
	}

	Blob* Asset::getBlob()
	{
		return m_blob;
	}

	std::vector<Enternity::Mesh>& Asset::getMeshs()
	{
		return m_meshs;
	}

	AssetLoadState Asset::getAssetLoadState()
	{
		return m_assetLoadState;
	}

	void Asset::reset()
	{
		SAFE_DELETE_SET_NULL(m_blob);
		m_meshs.clear();
		m_assetLoadState = AssetLoadState::Unloaded;
	}
}