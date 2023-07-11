#include "BlobLoader.h"
#include "ThreadPool.h"
#include "Common/Macro.h"

namespace Enternity
{
	BlobLoader::BlobLoader(const std::string& storagePath) :
		m_storagePath(storagePath),
		m_blob(nullptr),
		m_loadingState(loading_state_pending)
	{

	}

	BlobLoader::~BlobLoader()
	{
		SAFE_DELETE_SET_NULL(m_blob);
	}

	void BlobLoader::load(LoadingPriority priority)
	{
		if (priority == loading_priority_asyn)
		{
			ThreadPool::GetInstance().commitTask(std::bind(&BlobLoader::doLoad, this));
		}
		else
		{
			doLoad();
		}
	}
}