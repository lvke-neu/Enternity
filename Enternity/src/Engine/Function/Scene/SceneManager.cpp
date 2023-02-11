#include "SceneManager.h"
#include "Function/Render/RenderSystem.h"

namespace Enternity
{
	void SceneManager::tick()
	{
		RenderSystem::GetInstance().drawCall(&m_scene);
	}
}