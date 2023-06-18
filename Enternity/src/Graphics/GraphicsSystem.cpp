#include "GraphicsSystem.h"
#include "RHI/Texture/TextureProvider.h"
#include "RHI/Renderer/RendererProvider.h"

namespace Enternity
{
	GraphicsSystem::GraphicsSystem()
	{
		m_textureProvider = new TextureProvider;
	}

	GraphicsSystem::~GraphicsSystem()
	{
		SAFE_DELETE_SET_NULL(m_textureProvider);
		SAFE_DELETE_SET_NULL(m_rendererProvider)
	}
}



