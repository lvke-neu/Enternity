#include "Asset.h"
#include "AssetLoader.h"
#include "Utility/Utility.h"

namespace Enternity
{
	Asset::~Asset()
	{
		SAFE_DELETE_SET_NULL(m_assetLoader);
	}
}