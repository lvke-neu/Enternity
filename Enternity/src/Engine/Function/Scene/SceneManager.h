/***************************************************************************************
Author: lvke
Date:2023/2/11 14:14
Description:
SceneManager
****************************************************************************************/
#pragma once
#include "Scene.h"

namespace Enternity
{
	class SceneManager
	{
		SINGLETON(SceneManager);
		PRIVATE(SceneManager);
	public:
		void initialize();
		void uninitialize();
	public:
		void tick();
		Scene* getScene();
	private:
		//TODO:remove, just for test one scene
		Scene m_scene;
	};
}