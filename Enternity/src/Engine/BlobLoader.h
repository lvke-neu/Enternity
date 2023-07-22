#pragma once
#include <string>
#include <mutex>

namespace Enternity
{
	class BlobHolder;
	class BlobLoader
	{
		friend class BlobLoaderManager;
	public:
		BlobLoader(const char* storagePath);
		virtual ~BlobLoader();
	public:
		virtual BlobHolder* createBlobHolder(const char* path);
		virtual void doLoad(BlobHolder* blobHolder) = 0;
	protected:
		std::string m_storagePath;
		std::mutex m_mtx;
	};
}