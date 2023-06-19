#include "GraphicsSystem.h"
#include "RHI/Texture/TextureProvider.h"
#include "RHI/Renderer/RendererProvider.h"
#include "RHI/Mesh/MeshProvider.h"

namespace Enternity
{
	GraphicsSystem::GraphicsSystem()
	{
		m_textureProvider = new TextureProvider;
		m_rendererProvider = new RendererProvider;
		m_meshProvider = new MeshProvider;
	}

	GraphicsSystem::~GraphicsSystem()
	{
		SAFE_DELETE_SET_NULL(m_textureProvider);
		SAFE_DELETE_SET_NULL(m_rendererProvider)
		SAFE_DELETE_SET_NULL(m_meshProvider)
	}
}



