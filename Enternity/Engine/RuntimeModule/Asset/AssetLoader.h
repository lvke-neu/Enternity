#pragma once
#include <string>

namespace Enternity
{
	class Blob;
	class AssetLoader
	{
	public:
		virtual Blob* doLoad(const std::string& assetID) = 0;
	};
}