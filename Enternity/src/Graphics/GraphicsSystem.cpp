#include "GraphicsSystem.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoaderManager.h"
#include "RHI/Renderer/RendererBlobLoader.h"
#include "RHI/Texture/TextureBlobLoader.h"
#include "RHI/Mesh/MeshBlobLoader.h"

namespace Enternity
{
	GraphicsSystem::GraphicsSystem()
	{
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new RendererBlobLoader);
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new TextureBlobLoader);
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new MeshBlobLoader);
	}

	GraphicsSystem::~GraphicsSystem()
	{

	}
}



