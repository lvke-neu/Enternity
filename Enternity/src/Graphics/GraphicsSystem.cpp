#include "GraphicsSystem.h"
#include "RHI/TextureProvider.h"

namespace Enternity
{
	GraphicsSystem::GraphicsSystem()
	{
		m_textureProvider = new TextureProvider;
	}

	GraphicsSystem::~GraphicsSystem()
	{
		SAFE_DELETE_SET_NULL(m_textureProvider);
	}
}



