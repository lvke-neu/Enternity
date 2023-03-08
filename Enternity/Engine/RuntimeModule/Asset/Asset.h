#pragma once
#include <string>

namespace Enternity
{
	class Blob;
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
		inline Blob* getBlob() const;
		void setBlob(Blob* blob);
	protected:
		std::string m_assetID;
		AssetLoader* m_assetLoader;
		//only record the pointer
		Blob* m_blob;
	};

	inline std::string Asset::getAssetID() const
	{
		return m_assetID;
	}

	inline AssetLoader* Asset::getAssetLoader() const
	{
		return m_assetLoader;
	}

	inline Blob* Asset::getBlob() const
	{
		return m_blob;
	}

	inline void Asset::setBlob(Blob * blob)
	{
		m_blob = blob;
	}
}