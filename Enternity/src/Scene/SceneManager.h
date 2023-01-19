/***************************************************************************************
Author: lvke
Date:2023/1/2 16:10
Description:
SceneManager
****************************************************************************************/
#pragma once

#include <map>
#include "Macro/Macro.h"
#include "ECS/Entity/Entity.h"
#include "ECS/Component/Component.h"

BEGIN_ENTERNITY

class CameraController;
class SceneManager
{
	friend class SceneHierarchyPanel;
	friend class StatsPanel;
	friend class SceneSerializer;
	SINGLETON(SceneManager);
public:
	void Initialize();
	void Tick(float deltaTime);
	void OnResize(int width, int height);
	void Clear();

	inline Entity GetMainCameraEntity()
	{
		return m_MainCameraEntity;
	}
	bool IsWireFrame()
	{
		return m_MainCameraEntity.GetComponent<CameraComponent>().m_EnableWireframe;
	}
private:
	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = default;
	SceneManager& operator=(const SceneManager&) = default;

	void Update(float deltaTime);
	void DrawSkyBox();
private:
	entt::registry m_Registry;
	Entity m_MainCameraEntity;
	Entity m_SkyBoxEntity;

	std::map<unsigned int, Entity> m_Entities;
private:
	CameraController* m_CameraController{ nullptr };	
};

END_ENTERNITY