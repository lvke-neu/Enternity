#pragma once
#include <string>

namespace Enternity
{
	class Asset;
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
		virtual ~BlobHolder();
	public:
		void load(int priority = 1);
		void loadSucceeded__(Blob* blob);
		void loadFailed__();
		bool isLoadSucceeded();
		Blob* getBlob();
		const char* getPath();
		LoadingState getLoadingState();
		virtual Asset* createAsset();
	private:
		Blob* m_blob;
		LoadingState m_state;

		BlobLoader* m_blobLoader;
		std::string m_path;
	};

	inline bool BlobHolder::isLoadSucceeded()
	{
		return loading_state_succeeded == m_state;
	}

	inline Blob* BlobHolder::getBlob()
	{
		return m_blob;
	}

	inline const char* BlobHolder::getPath()
	{
		return m_path.c_str();
	}

	inline BlobHolder::LoadingState BlobHolder::getLoadingState()
	{
		return m_state;
	}
}