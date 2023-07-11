#pragma once
#include "../BlobLoader.h"

namespace Enternity
{
	class ShaderBlobLoader : public BlobLoader
	{
	public:
		ShaderBlobLoader();
		~ShaderBlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const AssetID& assetID) override;
	};

}