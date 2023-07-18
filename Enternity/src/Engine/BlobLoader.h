#pragma once
#include <string>

namespace Enternity
{
	class BlobHolder;
	class BlobLoader
	{
		friend class BlobLoaderManager;
	public:
		BlobLoader(const std::string& storagePath);
		virtual ~BlobLoader();
	public:
		BlobHolder* createBlobHolder(const std::string& path);
		virtual void doLoad(BlobHolder* blobHolder) = 0;
	private:
		std::string m_storagePath;
	};
}