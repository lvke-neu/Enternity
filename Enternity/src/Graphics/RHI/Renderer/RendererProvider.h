#pragma once
#include <functional>
#include <vector>

namespace Enternity
{
	class Renderer;
	class RendererAsset;
	class RendererProvider
	{
		struct Vs_Ps_FullPath 
		{
			Vs_Ps_FullPath() = default;
			~Vs_Ps_FullPath() = default;
			std::string vsFullPath;
			std::string psFullPath;
		};
		struct RendererAsset_Callback
		{
			RendererAsset* vsRendererAsset;
			RendererAsset* psRendererAsset;
			std::function<void(Renderer*)> callback;
		};
	public:
		RendererProvider();
		~RendererProvider();
	public:
		Renderer* getRendererSync(const char* vsFullPath, const char* psFullPath);
		void  getRendererAsyn(const char* vsFullPath, const char* psFullPath, std::function<void(Renderer*)> callback);
	private:
		void tick(void* data);
	private:
		std::vector <RendererAsset_Callback> m_map;
	};
}