#include "AssetID.h"

namespace Enternity
{
	
	AssetID::AssetID(const std::string& path) : 
		m_path(path)
	{

	}

	std::string AssetID::normalize()
	{
		auto pos = m_path.find("://");
		if (pos != m_path.npos)
		{
			return m_path.substr(pos + 3);
		}

		return "";
	}
}