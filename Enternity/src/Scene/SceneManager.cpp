#include "SceneManager.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoaderManager.h"
#include "Model/ModelBlobLoader.h"
#include "SceneGraph/Scene3D.h"

namespace Enternity
{
	SceneManager::SceneManager()
	{
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new ModelBlobLoader);
		m_currentScene = new Scene3D;
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SET_NULL(m_currentScene);
	}

	void SceneManager::tick()
	{
		m_currentScene->tick();
	}
}