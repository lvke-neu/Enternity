#pragma once
#include "RuntimeModule/Asset/AssetLoader.h"

namespace Enternity
{
	class TextAssetLoader : public AssetLoader
	{
	public:
		virtual Blob* doLoad(const std::string& assetID) override;
	};
}