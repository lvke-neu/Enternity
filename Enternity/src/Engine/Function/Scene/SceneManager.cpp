#include "SceneManager.h"

namespace Enternity
{
	void SceneManager::initialize()
	{
		LOG_INFO("SceneManager initialization");
	}

	void SceneManager::uninitialize()
	{
		LOG_INFO("SceneManager uninitialization");
	}

	void SceneManager::tick()
	{
		m_scene.tick();
	}
}