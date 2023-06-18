#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class TextureProvider;
	class RendererProvider;
	class GraphicsSystem
	{
		friend class Engine;
	private:
		GraphicsSystem();
		~GraphicsSystem();
	public:
		TextureProvider* getTextureProvider();
		RendererProvider* getRendererProvider();
	private:
		TextureProvider* m_textureProvider{ nullptr };
		RendererProvider* m_rendererProvider{ nullptr };
	};

	inline TextureProvider* GraphicsSystem::getTextureProvider()
	{
		return m_textureProvider;
	}

	inline RendererProvider* GraphicsSystem::getRendererProvider()
	{
		return m_rendererProvider;
	}
}