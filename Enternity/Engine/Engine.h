#pragma once
#include "Utility/Utility.h"
#include <unordered_map>
#include <string>

namespace Enternity
{
	class IRuntimeModule;
	class AssetManager;
	class GraphicsManager;
	class SceneManager;
	class Engine
	{
		SINGLETON(Engine);
	public:
		bool Initialize();
		void Finalize();
		void Tick();

		bool IsQuit();
	public:
		IRuntimeModule* GetRuntimeModule(const std::string& moduleName);
	private:
		AssetManager* m_pAssetManager;
		GraphicsManager* m_pGraphicsManager;
		SceneManager* m_pSceneManager;

		std::unordered_map<std::string, IRuntimeModule*> m_runtimeModules;
	};
}