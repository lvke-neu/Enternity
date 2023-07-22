#include "RendererBlobHolder.h"
#include "Renderer.h"

namespace Enternity
{
	RendererBlobHolder::RendererBlobHolder(BlobLoader* blobLoader, const std::string& path) :
		BlobHolder(blobLoader, path)
	{

	}

	Asset* RendererBlobHolder::createAsset()
	{
		return new Renderer;
	}
}