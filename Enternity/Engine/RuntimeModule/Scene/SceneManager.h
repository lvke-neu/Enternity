#pragma once
#include "RuntimeModule/Interface/IRuntimeModule.h"
#include <unordered_map>

namespace Enternity
{
	class Scene;
	class SceneManager : public IRuntimeModule
	{
	public:
		virtual ~SceneManager() = default;

		virtual bool Initialize() override;
		virtual void Finalize() override;
		virtual void Tick() override;
	public:
		void loadScene(const char* sceneFilepath);
	
	private:
		Scene* m_scene;
	};
}