#include "SceneManager.h"
#include "Scene.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"

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

	void SceneManager::tick(float deltaTime)
	{
		m_currentScene->tick(deltaTime);
		Engine::GetInstance().getGraphicsSystem()->render(m_currentScene);
	}
}