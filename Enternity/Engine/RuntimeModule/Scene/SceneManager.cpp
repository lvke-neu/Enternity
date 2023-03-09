#include "SceneManager.h"
#include "Scene.h"

#include "SceneAsset.h"
#include "RuntimeModule/Asset/AssetManager.h"
#include "Engine/Engine.h"
#include "Core/Blob/Blob.h"

namespace Enternity
{
	bool SceneManager::Initialize()
	{
		return true;
	}

	void SceneManager::Finalize()
	{

	}

	void SceneManager::Tick()
	{
		int i = 0;
		i++;
	}

	void SceneManager::loadScene(const char* sceneFilepath)
	{
		SceneAsset sceneAsset;
		sceneAsset.setPath(sceneFilepath);

		((AssetManager*)Engine::GetInstance().GetRuntimeModule("AssetManager"))->loadAsset(sceneAsset, AseetLoadType::Asyn);


		m_scene = new Scene;
		m_scene->m_ogex = std::string((char*)sceneAsset.getBlob()->getData(), sceneAsset.getBlob()->getLength());
	}
}