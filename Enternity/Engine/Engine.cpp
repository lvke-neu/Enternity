#include "Engine.h"
#include "RuntimeModule/Graphics/GraphicsManager.h"
#include "RuntimeModule/Memory/MemoryManager.h"

namespace Enternity
{
	bool Engine::Initialize()
	{
		m_pGraphicsManager = new GraphicsManager;
		m_pGraphicsManager->Initialize();
		m_runtimeModules["GraphicsManager"] = m_pGraphicsManager;

		m_pMemoryManager = new MemoryManager;
		m_pMemoryManager->Initialize();
		m_runtimeModules["MemoryManager"] = m_pMemoryManager;

		return true;
	}

	void Engine::Finalize()
	{
		m_pGraphicsManager->Finalize();
		SAFE_DELETE_SET_NULL(m_pGraphicsManager);

		m_pMemoryManager->Finalize();
		SAFE_DELETE_SET_NULL(m_pGraphicsManager);
		
		m_runtimeModules.clear();
	}

	void Engine::Tick()
	{
		m_pGraphicsManager->Tick();
		m_pMemoryManager->Tick();
	}

	IRuntimeModule* Enternity::Engine::GetRuntimeModule(const std::string& moduleName)
	{
		auto iter = m_runtimeModules.find(moduleName);
		if (iter != m_runtimeModules.end())
		{
			return iter->second;
		}

		return nullptr;
	}
}


