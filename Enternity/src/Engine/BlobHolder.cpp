#include "BlobHolder.h"
#include "Blob.h"
#include "ThreadPool.h"

namespace Enternity
{
	BlobHolder::BlobHolder(const AssetID& assetID) :
		m_blob(nullptr),
		m_state(loading_state_pending),
		m_assetID(assetID)
	{

	}

	BlobHolder::~BlobHolder()
	{
		SAFE_DELETE_SET_NULL(m_blob);
	}

	void BlobHolder::load()
	{
		ThreadPool::GetInstance().commitTask(std::bind(&BlobHolder::doLoad, this));
	}
}