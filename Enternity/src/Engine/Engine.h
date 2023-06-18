#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class Timer;
	class RenderView;
	class GraphicsSystem;
	class Engine
	{
		SINGLETON(Engine);
		PRIVATE(Engine);
	public:
		void initialize();
		void uninitialize();
		void run();
	public:
		GraphicsSystem* getGraphicsSystem();
	private:
		GraphicsSystem* m_graphicsSystem{ nullptr };
		RenderView* m_renderView{ nullptr };
		Timer* m_timer{ nullptr };
	};

	inline GraphicsSystem* Engine::getGraphicsSystem()
	{
		return m_graphicsSystem;
	}
}