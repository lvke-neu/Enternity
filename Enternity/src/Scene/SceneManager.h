/***************************************************************************************
Author: lvke
Date:2023/1/2 16:10
Description:
SceneManager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "ECS/Entity/Entity.h"
#include "ECS/Component/Component.h"

BEGIN_ENTERNITY

class CameraController;
class SceneHierarchyPanel;
class SceneManager
{
	SINGLETON(SceneManager);
public:
	void Initialize();
	void Tick(float deltaTime);
	void OnResize(int width, int height);
private:
	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = default;
	SceneManager& operator=(const SceneManager&) = default;
private:
	entt::registry m_Registry;

	Entity m_MainCameraEntity;
	Entity m_CubeEntity;
	Entity m_PlaneEntity;
private:
	CameraController* m_CameraController{ nullptr };	
	SceneHierarchyPanel* m_SceneHierarchyPanel{ nullptr };
};

END_ENTERNITY