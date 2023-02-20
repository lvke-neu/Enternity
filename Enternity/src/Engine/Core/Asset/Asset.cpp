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
		m_assetLoadState(AssetLoadState::unloaded)
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

	Blob** Asset::getBlob()
	{
		return m_blob;
	}

	AssetLoadState Asset::getAssetLoadState()
	{
		return m_assetLoadState;
	}

	void Asset::reset()
	{
		for (int i = 0; i < 10; i++)
			if (m_blob[i])
				SAFE_DELETE_SET_NULL(m_blob[i]);

		m_assetLoadState = AssetLoadState::unloaded;
	}
}