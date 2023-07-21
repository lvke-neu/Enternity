#include "Renderer.h"
#include "RendererBlobHolder.h"

namespace Enternity
{
	void Renderer::load(BlobHolder* blobHolder)
	{
		RendererBlobHolder* rendererBlobHolder = dynamic_cast<RendererBlobHolder*>(blobHolder);
		if (!rendererBlobHolder)
		{
			return;
		}

		m_renderId = 123;
	}
}