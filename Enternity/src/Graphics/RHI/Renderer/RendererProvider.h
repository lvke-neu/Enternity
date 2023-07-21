#pragma once
#include <vector>

namespace Enternity
{
	class Renderer;
	class BlobHolder;
	class RendererProvider
	{
	public:
		RendererProvider();
		~RendererProvider();
	public:
		Renderer* getRenderer(const char* path);
	private:
		void tick(void* data);

	};
}