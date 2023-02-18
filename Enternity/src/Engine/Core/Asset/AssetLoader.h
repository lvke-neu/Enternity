/***************************************************************************************
Author: lvke
Date:2023/2/18 14:33
Description:
AssetLoader
****************************************************************************************/
#pragma once

namespace Enternity
{
	class Asset;
	class AssetLoader
	{
	public:
		void loadAsset(Asset& asset);
	private:
		void loadShaderImpl(Asset& asset);
		void loadTextureImpl(Asset& asset);
		void loadMeshImpl(Asset& asset);
	};
}