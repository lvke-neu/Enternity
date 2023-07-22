#pragma once
#include <vector>

namespace Enternity
{
	class BlobLoader;
	class BlobLoaderManager
	{
		friend class Engine;
	private:
		BlobLoaderManager();
		~BlobLoaderManager();
	public:
		void registerBlobLoader(BlobLoader* blobLoader);
		BlobLoader* getBlobLoader(const char* path);
	private:
		std::vector<BlobLoader*> m_blobLoaders;
	};

}