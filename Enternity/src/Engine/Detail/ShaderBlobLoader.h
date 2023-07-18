#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class ShaderBlobLoader : public BlobLoader
	{
	public:
		ShaderBlobLoader();
	public:
		virtual void doLoad(BlobHolder* blobHolder) override;
	};
}