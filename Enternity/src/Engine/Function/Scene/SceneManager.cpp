#include "SceneManager.h"
#include "Core/Log/Log.h"
#include "Chapter/Common/InputLayout.h"
#include "Chapter/Detail/Chapter1.h"


namespace Enternity
{
	void SceneManager::initialize()
	{
		InputLayout::Init();
		LOG_INFO("SceneManager initialization");
	}

	void SceneManager::uninitialize()
	{
		LOG_INFO("SceneManager uninitialization");
		SAFE_DELETE_SET_NULL(m_currentScene);
	}

	void SceneManager::setChpater(const std::string& chapter)
	{
		SAFE_DELETE_SET_NULL(m_currentScene);
		m_currentScene = new Chapter1;
	}

	void SceneManager::tick(float deltaTime)
	{
		if(m_currentScene)
			m_currentScene->tick(deltaTime);
	}
}