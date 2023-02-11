/***************************************************************************************
Author: lvke
Date:2023/2/11 14:14
Description:
SceneManager
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include "Scene.h"

namespace Enternity
{
	class SceneManager
	{
		SINGLETON(SceneManager);
		PRIVATE(SceneManager);
	public:
		void tick();
	private:
		//TODO:remove, just for test one scene
		Scene m_scene;
	};
}