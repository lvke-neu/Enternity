#pragma once
#include "Utility/Utility.h"
#include <string>
#include <unordered_map>

namespace Enternity
{
	class IScene;
	class SceneManager
	{
		SINGLETON(SceneManager);
	public:
		void Initialize();
		void Finalize();
		void Tick(float deltaTime);
		void LoadScene(const std::string& sceneName);
		void OnResize(int width, int height);
		void RenderGUI();
		void RecompileCurrentSceneShader();
	private:
		std::unordered_map<std::string, IScene*> m_scenes;
		IScene* m_currentScene;
	};
}