#pragma once
#include <string>

namespace Enternity
{
	class Blob;
	class BlobLoader
	{
	public:
		enum LoadingPriority
		{
			loading_priority_sync,
			loading_priority_asyn
		};
		enum LoadingState
		{
			loading_state_pending,
			loading_state_succeeded,
			loading_state_failed
		};
	public:
		BlobLoader(const std::string& storagePath);
		virtual ~BlobLoader();
	public:
		void load(LoadingPriority priority);
	private:
		virtual void doLoad() = 0;
	private:
		std::string m_storagePath;
		Blob* m_blob;
		LoadingState m_loadingState;
	};
}