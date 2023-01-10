/***************************************************************************************
Author: lvke
Date:2023/1/2 16:10
Description:
SceneManager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include <entt.hpp>

BEGIN_ENTERNITY

class CameraController;
class Entity;
class SceneManager
{
	SINGLETON(SceneManager);
public:
	static entt::registry s_Registry;
public:
	void Tick(float deltaTime);
private:
	SceneManager();
	~SceneManager();
	SceneManager(const SceneManager&) = default;
	SceneManager& operator=(const SceneManager&) = default;
private:
	CameraController* m_CameraController{ nullptr };
private:
	void InitializeComponet();
	Entity* m_CubeEntity;
};

END_ENTERNITY