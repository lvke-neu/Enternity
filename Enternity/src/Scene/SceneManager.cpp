#include "SceneManager.h"
#include "Scene.h"
#include "Common/Macro.h"
#include "Engine/Engine.h"
#include "Engine/BlobLoaderManager.h"
#include "Model/ModelBlobLoader.h"

namespace Enternity
{
	SceneManager::SceneManager()
	{
		Engine::GetInstance().getBlobLoaderManager()->registerBlobLoader(new ModelBlobLoader);
		m_currentScene = new Scene;	
	}

	SceneManager::~SceneManager()
	{
		SAFE_DELETE_SET_NULL(m_currentScene);
	}

	void SceneManager::tick(float deltaTime)
	{
		//m_currentScene->tick(deltaTime);
	}
}