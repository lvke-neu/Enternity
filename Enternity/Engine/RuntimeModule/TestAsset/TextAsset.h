#pragma once

#include "../Asset/Asset.h"

namespace Enternity
{
	class TextAsset : public Asset
	{
	public:
		TextAsset(const std::string& assetID, AssetLoader* assetLoader) : Asset(assetID, assetLoader)
		{

		}
	};
}