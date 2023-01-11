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
#include "Event/ImguiDrawEventManager.h"

BEGIN_ENTERNITY

class CameraController;
class SceneManager : public ImguiDrawEvent
{
	SINGLETON(SceneManager);
public:
	void Initialize();
	void Tick(float deltaTime);
	void OnResize(int width, int height);
	virtual void ImguiDraw() override;
private:
	SceneManager() = default;
	~SceneManager();
	SceneManager(const SceneManager&) = default;
	SceneManager& operator=(const SceneManager&) = default;
private:
	void InitializeComponent();
private:
	entt::registry m_Registry;
	Entity m_CameraEntity;
	CameraController* m_CameraController{ nullptr };

	Entity m_CubeEntity;	
};

END_ENTERNITY