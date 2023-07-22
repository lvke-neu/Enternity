#include "RendererBlobHolder.h"
#include "Renderer.h"

namespace Enternity
{
	RendererBlobHolder::RendererBlobHolder(BlobLoader* blobLoader, const char* path) :
		BlobHolder(blobLoader, path)
	{

	}

	Asset* RendererBlobHolder::createAsset()
	{
		return new Renderer;
	}
}