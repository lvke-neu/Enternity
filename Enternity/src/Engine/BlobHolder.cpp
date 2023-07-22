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
		auto pos = m_path.find("://");
		if (pos != m_path.npos)
		{
			m_path = m_path.substr(pos + 3);
		}
	}

	BlobHolder::~BlobHolder()
	{
		SAFE_DELETE_SET_NULL(m_blob);
	}

	void BlobHolder::load()
	{
		ThreadPool::GetInstance().commitTask(std::bind(&BlobLoader::doLoad, m_blobLoader, this));
	}

	void BlobHolder::loadSucceeded__(Blob* blob)
	{
		SAFE_DELETE_SET_NULL(m_blob);
		m_blob = new Blob(blob->getLength());
		memcpy_s(m_blob->getData(), m_blob->getLength(), blob->getData(), m_blob->getLength());
		m_state = loading_state_succeeded;
	}

	void BlobHolder::loadFailed__()
	{
		SAFE_DELETE_SET_NULL(m_blob);
		m_state = loading_state_failed;
	}

	Asset* BlobHolder::createAsset()
	{
		return nullptr;
	}
}