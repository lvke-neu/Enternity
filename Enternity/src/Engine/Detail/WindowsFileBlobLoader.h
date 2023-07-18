#pragma once
#include "Engine/BlobLoader.h"

namespace Enternity
{
	class WindowsFileBlobLoader : public BlobLoader
	{
	public:
		WindowsFileBlobLoader();
	public:
		virtual void doLoad(BlobHolder* blobHolder) override;
	};
}