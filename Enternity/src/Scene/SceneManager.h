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

enum SceneState
{
	Editor,
	Player
};

class CameraController;
class BulletSimulation;
class SceneManager
{
	friend class SceneHierarchyPanel;
	friend class ViewportPanel;
	friend class StatsPanel;
	friend class SceneSerializer;
	friend class PlayButtonPanel;

	SINGLETON(SceneManager);
public:
	void Initialize();
	void Tick(float deltaTime);
	void OnResize(int width, int height);
	void Clear();

	inline Entity GetMainCameraEntity()
	{
		return m_EditorCameraEntity;
	}
	bool IsWireFrame()
	{
		return m_EditorCameraEntity.GetComponent<CameraComponent>().m_EnableWireframe;
	}

	Entity& GetCurrentCameraEntity()
	{
		return m_SceneState == SceneState::Editor ? m_EditorCameraEntity : m_PlayerCameraEntity;
	}

	SceneState GetCurrentSceneState()
	{
		return m_SceneState;
	}

	entt::registry* GetRegistry()
	{
		return &m_Registry;
	}

	void OnPlay();
	void OnEditor();
private:
	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = default;
	SceneManager& operator=(const SceneManager&) = default;
private:
	entt::registry m_Registry;
	Entity m_EditorCameraEntity;
	Entity m_PlayerCameraEntity;
	Entity m_SkyBoxEntity;
	Entity m_DirectionLightEntity;

	std::map<unsigned int, Entity> m_Entities;
	std::vector<TransformComponent> m_EditorEntityTrans;
private:
	CameraController* m_EditorCameraController{ nullptr };	
	CameraController* m_PlayerCameraController{ nullptr };
	BulletSimulation* m_BulletSimulation{ nullptr };
private:
	SceneState m_SceneState = SceneState::Editor;
};

END_ENTERNITY