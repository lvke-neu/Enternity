#pragma once
#include "Common/Macro.h"

namespace Enternity
{
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
	};

	inline GraphicsSystem* Engine::getGraphicsSystem()
	{
		return m_graphicsSystem;
	}
}