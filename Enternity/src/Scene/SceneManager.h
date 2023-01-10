/***************************************************************************************
Author: lvke
Date:2023/1/2 16:10
Description:
SceneManager
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "ECS/Entity/Entity.h"
#include "Event/ImguiDrawEventManager.h"

BEGIN_ENTERNITY

class CameraController;
class SceneManager : public ImguiDrawEvent
{
	SINGLETON(SceneManager);
public:
	void Tick(float deltaTime);
	virtual void ImguiDraw() override;
private:
	SceneManager();
	~SceneManager();
	SceneManager(const SceneManager&) = default;
	SceneManager& operator=(const SceneManager&) = default;
private:
	CameraController* m_CameraController{ nullptr };
private:
	entt::registry m_Registry;
private:
	void InitializeComponent();
	Entity m_CubeEntity;
};

END_ENTERNITY