#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class TextureProvider;
	class RendererProvider;
	class MeshProvider;
	class GraphicsSystem
	{
		friend class Engine;
	private:
		GraphicsSystem();
		~GraphicsSystem();
	public:
		TextureProvider* getTextureProvider();
		RendererProvider* getRendererProvider();
		MeshProvider* getMeshProvider();
	private:
		TextureProvider* m_textureProvider{ nullptr };
		RendererProvider* m_rendererProvider{ nullptr };
		MeshProvider* m_meshProvider{ nullptr };
	};

	inline TextureProvider* GraphicsSystem::getTextureProvider()
	{
		return m_textureProvider;
	}

	inline RendererProvider* GraphicsSystem::getRendererProvider()
	{
		return m_rendererProvider;
	}

	inline MeshProvider* GraphicsSystem::getMeshProvider()
	{
		return m_meshProvider;
	}
}