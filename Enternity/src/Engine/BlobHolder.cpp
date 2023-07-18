#include "BlobHolder.h"
#include "Blob.h"
#include "BlobLoader.h"
#include "ThreadPool.h"

namespace Enternity
{
	BlobHolder::BlobHolder(BlobLoader* blobLoader, const std::string& path) :
		m_blob(nullptr),
		m_state(loading_state_pending),
		m_blobLoader(blobLoader),
		m_path(path)
	{

	}

	BlobHolder::~BlobHolder()
	{
		SAFE_DELETE_SET_NULL(m_blob);
	}

	void BlobHolder::load()
	{
		ThreadPool::GetInstance().commitTask(std::bind(&BlobLoader::doLoad, m_blobLoader, this));
	}
}