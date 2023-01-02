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

class CameraController : public TickEvent
{
public:
	CameraController();
	~CameraController();
	CameraController(const CameraController&) = delete;
	CameraController& operator=(const CameraController&) = delete;
public:
	virtual void tick(float deltaTime) override;
private:
	float m_MoveSpeed = 10.0f;
};

END_ENTERNITY