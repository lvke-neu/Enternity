#pragma once
#include <string>

namespace Enternity
{
	class Blob;
	class BlobLoader;
	class BlobHolder
	{
	public:
		enum LoadingState
		{
			loading_state_pending,
			loading_state_succeeded,
			loading_state_failed
		};
	public:
		BlobHolder(BlobLoader* blobLoader, const std::string& path);
		~BlobHolder();
	public:
		void load();
	protected:
		Blob* m_blob;
		LoadingState m_state;

		BlobLoader* m_blobLoader;
		std::string m_path;
	};
}