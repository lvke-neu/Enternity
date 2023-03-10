/***************************************************************************************
Author: lvke
Date:2023/1/2 15:57
Description:
Camera Controller
****************************************************************************************/
#pragma once
#include "Macro/Macro.h"
#include "Event/InputEventManager.h"
#include "Event/TickEventManager.h"
#include "ECS/Entity/Entity.h"

BEGIN_ENTERNITY

class Entity;
class CameraController : public InputEvent, public TickEvent
{
public:
	CameraController(Entity cameraEntity);
	~CameraController();
	CameraController(const CameraController&) = delete;
	CameraController& operator=(const CameraController&) = delete;

	void Pause()
	{
		InputEventManager::GetInstance().UnRegisterEvent((this));
		TickEventManager::GetInstance().UnRegisterEvent(this);
	}
	void Start()
	{
		InputEventManager::GetInstance().RegisterEvent((this));
		TickEventManager::GetInstance().RegisterEvent(this);
	}
public:
	virtual void onMousePress(MouseState mouseState) override;
	virtual void onMouseRelease(MouseState mouseState) override;
	virtual void onMouseMove(MouseState mouseState) override;
	virtual void onMouseWheel(MouseState mouseState) override;

	virtual void tick(float deltaTime) override;
private:
	int m_oldMousePosX;
	int m_oldMousePosY;
	int m_deltaMousePosX = 0;
	int m_deltaMousePosY = 0;

	Entity m_CameraEntity;
};

END_ENTERNITY