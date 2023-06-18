#pragma once
//TODO:remove
#include <string>

namespace Enternity
{
	class RendererAsset;
	class Renderer
	{
	public:
		Renderer(RendererAsset* vsRendererAsset, RendererAsset* psRendererAsset, RendererAsset* gsRendererAsset = nullptr);
		~Renderer();
	//TODO:remove
	private:
		std::string m_vs{ "" };
		std::string m_ps{ "" };
	};
}