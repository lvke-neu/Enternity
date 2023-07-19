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
		BlobLoader(const std::string& storagePath);
		virtual ~BlobLoader();
	public:
		BlobHolder* createBlobHolder(const std::string& path);
		virtual void doLoad(BlobHolder* blobHolder) = 0;
	protected:
		std::string m_storagePath;
		std::mutex m_mtx;
	};
}