#include "RendererProvider.h"
#include "RendererBlobLoader.h"
#include "Engine/Engine.h"
#include "Engine/BlobHolder.h"
#include "Engine/BlobLoaderManager.h"
#include "Renderer.h"

namespace Enternity
{

	RendererProvider::RendererProvider()
	{
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new RendererBlobLoader);
	}

	void RendererProvider::tick(void* data)
	{
		for (auto it = m_task.begin(); it != m_task.end(); )
		{
			if (it->blobHolder->isLoadSucceeded())
			{
				RHIAsset* rhiAsset = new Renderer;
				rhiAsset->load(it->blobHolder);
				it->callback(rhiAsset);
				SAFE_DELETE_SET_NULL(it->blobHolder);
				it = m_task.erase(it);
			}
			else
			{
				it++;
			}
		}
	}

}