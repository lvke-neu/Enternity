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

BEGIN_ENTERNITY

class Entity;
class CameraController : public InputEvent, public TickEvent
{
public:
	CameraController(Entity* cameraEntity);
	~CameraController();
	CameraController(const CameraController&) = delete;
	CameraController& operator=(const CameraController&) = delete;
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

	Entity* m_CameraEntity{ nullptr };
};

END_ENTERNITY