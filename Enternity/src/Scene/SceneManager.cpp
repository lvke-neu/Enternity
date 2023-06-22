#include "SceneManager.h"
#include "Scene.h"
#include "Common/Macro.h"

namespace Enternity
{
	SceneManager::SceneManager()
	{
		m_currentScene = new Scene;
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SET_NULL(m_currentScene);
	}

	void SceneManager::onUpdateTime(float deltaTime)
	{
		m_currentScene->onUpdateTime(deltaTime);
	}
}