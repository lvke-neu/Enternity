/***************************************************************************************
Author: lvke
Date:2023/2/11 14:14
Description:
SceneManager
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include <string>

namespace Enternity
{
	class IScene;
	class SceneManager
	{
		SINGLETON(SceneManager);
		PRIVATE(SceneManager);
	public:
		void initialize();
		void uninitialize();
	public:
		void setChpater(const std::string& chapter);
	public:
		void tick(float deltaTime);
	private:
		IScene* m_currentScene{ nullptr };
	};
}