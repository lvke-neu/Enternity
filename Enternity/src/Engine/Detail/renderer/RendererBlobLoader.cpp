#include "RendererBlobLoader.h"
#include "Engine/Blob.h"
#include "Engine/BlobHolder.h"
#include "Engine/Log.h"
#include "RendererBlobHolder.h"
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

		RendererBlobHolder* rendererBlobHolder = dynamic_cast<RendererBlobHolder*>(blobHolder);
		if (!rendererBlobHolder)
			return;

		m_mtx.lock();

		std::ifstream ifs(rendererBlobHolder->getPath(), std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			rendererBlobHolder->loadFailed__();
			LOG_ERROR("Renderer load failed:{0}", rendererBlobHolder->getPath());
			m_mtx.unlock();
			return;
		}

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		Blob* blob = new Blob(size);
		pFilebuf->sgetn((char*)blob->getData(), blob->getLength());

		ifs.close();

		rendererBlobHolder->loadSucceeded__(blob);
		SAFE_DELETE_SET_NULL(blob);

		m_mtx.unlock();
	}
}