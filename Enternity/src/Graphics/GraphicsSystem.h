#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class TextureProvider;
	class GraphicsSystem
	{
		friend class Engine;
	private:
		GraphicsSystem();
		~GraphicsSystem();
	public:
		TextureProvider* getTextureProvider();
	private:
		TextureProvider* m_textureProvider{ nullptr };
	};

	inline TextureProvider* GraphicsSystem::getTextureProvider()
	{
		return m_textureProvider;
	}
}