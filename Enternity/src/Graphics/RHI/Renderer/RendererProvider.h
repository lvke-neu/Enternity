#pragma once

namespace Enternity
{
	class Renderer;
	class RendererProvider
	{
	public:
		Renderer* getRenderer(const char* vsFullPath, const char* psFullPath);
	};
}