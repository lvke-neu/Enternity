#pragma once
#include <string>

namespace Enternity
{
	class AssetLoader;
	class Asset
	{
	public:
		Asset(const std::string& assetID, AssetLoader* assetLoader) : m_assetID(assetID), m_assetLoader(assetLoader) 
		{
		
		}
		virtual ~Asset();

		inline std::string getAssetID() const;
		inline AssetLoader* getAssetLoader() const;
	protected:
		std::string m_assetID;
		AssetLoader* m_assetLoader;
	};

	inline std::string Asset::getAssetID() const
	{
		return m_assetID;
	}

	inline AssetLoader* Asset::getAssetLoader() const
	{
		return m_assetLoader;
	}

}