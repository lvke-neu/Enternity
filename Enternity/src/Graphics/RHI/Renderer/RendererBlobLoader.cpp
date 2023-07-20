#include "RendererBlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/BlobHolder.h"
#include "Engine/Log.h"
#include <fstream>

namespace Enternity
{
	RendererBlobLoader::RendererBlobLoader() : BlobLoader("renderer://")
	{

	}

	void RendererBlobLoader::doLoad(BlobHolder* blobHolder)
	{
		if (blobHolder->getLoadingState() != BlobHolder::loading_state_pending)
			return;

		m_mtx.lock();

		std::ifstream ifs(blobHolder->getPath(), std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			blobHolder->loadFailed__();
			LOG_ERROR("WindowsFile load failed:{0}", blobHolder->getPath());
			m_mtx.unlock();
			return;
		}

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		Blob* blob = new Blob(size);
		pFilebuf->sgetn((char*)blob->getData(), blob->getLength());

		ifs.close();

		blobHolder->loadSucceeded__(blob);
		SAFE_DELETE_SET_NULL(blob);

		m_mtx.unlock();
	}
}