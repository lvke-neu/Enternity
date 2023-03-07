#include "Engine.h"
#include "RuntimeModule/Graphics/GraphicsManager.h"
#include "RuntimeModule/Asset/AssetManager.h"

namespace Enternity
{
	bool Engine::Initialize()
	{
		m_pAssetManager = new AssetManager;
		m_pAssetManager->Initialize();
		m_runtimeModules["AssetManager"] = m_pAssetManager;

		m_pGraphicsManager = new GraphicsManager;
		m_pGraphicsManager->Initialize();
		m_runtimeModules["GraphicsManager"] = m_pGraphicsManager;

		return true;
	}

	void Engine::Finalize()
	{
		m_pAssetManager->Finalize();
		SAFE_DELETE_SET_NULL(m_pAssetManager);

		m_pGraphicsManager->Finalize();
		SAFE_DELETE_SET_NULL(m_pGraphicsManager);

		m_runtimeModules.clear();
	}

	void Engine::Tick()
	{
		m_pAssetManager->Tick();
		m_pGraphicsManager->Tick();
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


