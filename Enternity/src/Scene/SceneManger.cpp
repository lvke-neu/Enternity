#include "SceneManager.h"
#include "Utility/Utility.h"
#include "Interface/SceneInterface.h"
#include "Core/Reflection/Reflection.h"

namespace Enternity
{
	void SceneManager::Initialize()
	{
		m_currentScene = nullptr;
	}

	void SceneManager::Finalize()
	{
		for (auto& scene : m_scenes)
		{
			SAFE_DELETE_SET_NULL(scene.second);
		}

		m_scenes.clear();
	}

	void SceneManager::Tick(float deltaTime)
	{
		if (m_currentScene)
			m_currentScene->Tick(deltaTime);
	}

	void SceneManager::LoadScene(const std::string& sceneName)
	{
		auto iter = m_scenes.find(sceneName);
		if (iter == m_scenes.end())
		{
			m_scenes[sceneName] = Reflection<IScene>::getInstance().createObject(sceneName);
		}

		m_currentScene = m_scenes[sceneName];
		m_currentScene->Initialize();
	}

	void SceneManager::RecompileCurrentSceneShader()
	{
		if (m_currentScene)
			m_currentScene->RecompileShader();
	}

	void SceneManager::RenderGUI()
	{
		if (m_currentScene)
			m_currentScene->RenderGUI();
	}
}