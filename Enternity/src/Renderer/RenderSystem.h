/***************************************************************************************
Author: lvke
Date:2023/1/21 17:25
Description:
RenderSystem
****************************************************************************************/

#pragma once

#include "Macro/Macro.h"
#include "Scene/ECS/Entity/Entity.h"
#include "Scene/ECS/Component/Component.h"

BEGIN_ENTERNITY

class RenderSystem
{
	SINGLETON(RenderSystem);
	PRIVATE_FUCNTION(RenderSystem);
public:
	void DrawEntity(Entity& cameraEntity, Entity& entity, const Entity& lightEntity);
	void DrawSkyBox(Entity& cameraEntity, Entity& entity);
	void DrawModel(Entity& cameraEntity, Entity& entity, const Entity& lightEntity);

	void DrawColliderShape(Entity& cameraEntity, Entity& entity, const Entity& lightEntity);
};

END_ENTERNITY