/***************************************************************************************
Author: lvke
Date:2023/1/25 14:05
Description:
Bullet Simulation
****************************************************************************************/

#pragma once

#include "Macro/Macro.h"
#include "Scene/ECS/Entity/Entity.h"
#include "Scene/ECS/Component/Component.h"
#include "Event/TickEventManager.h"
#include "Event/InputEventManager.h"

BEGIN_ENTERNITY

class BulletSimulation : public TickEvent, public InputEvent
{
public:
	BulletSimulation();
	~BulletSimulation();

	virtual void tick(float deltaTime) override;
	virtual void onMousePress(MouseState mouseState) override;
	virtual void onMouseRelease(MouseState mouseState) override;
private:
	Entity m_BulletEntity;
	bool m_IsLeftKeyPress = false;
};

END_ENTERNITY