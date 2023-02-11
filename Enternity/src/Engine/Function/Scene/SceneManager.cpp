#include "SceneManager.h"

namespace Enternity
{
	void SceneManager::tick(float deltaTime)
	{
		m_scene.tick(deltaTime);
	}
}