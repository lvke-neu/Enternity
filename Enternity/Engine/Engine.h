#pragma once
#include "Utility/Utility.h"
#include <unordered_map>
#include <string>

namespace Enternity
{
	class IRuntimeModule;
	class GraphicsManager;
	class MemoryManager;
	class Engine
	{
		SINGLETON(Engine);
	public:
		bool Initialize();
		void Finalize();
		void Tick();
	public:
		IRuntimeModule* GetRuntimeModule(const std::string& moduleName);
	private:
		GraphicsManager* m_pGraphicsManager;
		MemoryManager* m_pMemoryManager;

		std::unordered_map<std::string, IRuntimeModule*> m_runtimeModules;
	};
}