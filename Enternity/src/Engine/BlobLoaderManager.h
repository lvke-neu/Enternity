#pragma once
#include <string>
#include <vector>

namespace Enternity
{
	class BlobLoader;
	class BlobLoaderManager
	{
	public:
		BlobLoaderManager();
		~BlobLoaderManager();
	public:
		void registerBlobLoader(BlobLoader* blobLoader);
		BlobLoader* getBlobLoader(const std::string& path);
	private:
		std::vector<BlobLoader*> m_blobLoaders;
	};

}