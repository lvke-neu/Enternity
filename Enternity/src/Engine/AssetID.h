#pragma once
#include <string>

namespace Enternity
{
	class AssetID
	{
		friend class BlobLoaderManager;
	public:
		AssetID(const std::string& path);
		std::string normalize();
		const std::string& getPath() const;
	private: 
		std::string m_path;
	};

	inline const std::string& AssetID::getPath() const 
	{
		return m_path;
	}
}