/***************************************************************************************
Author: lvke
Date:2023/1/2 16:10
Description:
SceneManager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"

BEGIN_ENTERNITY

class Triangle;
class CameraController;
class SceneManager
{
	SINGLETON(SceneManager);
public:
	void Tick(float deltaTime);
private:
	SceneManager();
	~SceneManager();
	SceneManager(const SceneManager&) = default;
	SceneManager& operator=(const SceneManager&) = default;
private:
	Triangle* m_Triangle{nullptr};
	CameraController* m_CameraController{ nullptr };
};

END_ENTERNITY