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
#include "Shader.h"

BEGIN_ENTERNITY

class RenderSystem
{
	SINGLETON(RenderSystem);

private:
	RenderSystem();
	~RenderSystem();
	RenderSystem(const RenderSystem&) = default;
	RenderSystem& operator=(const RenderSystem&) = default;
public:
	void DrawEntity(Entity& cameraEntity, Entity& entity, const Entity& lightEntity);
	void DrawSkyBox(Entity& cameraEntity, Entity& entity);
	void DrawShadowMap(Entity& entity, const Entity& lightEntity);
	void DrawColliderShape(Entity& cameraEntity, Entity& entity, const Entity& lightEntity);
private:
	Shader* m_ShadowMapShader{ nullptr };
	glm::mat4 m_LightOrthoProjectMatrix;
};

END_ENTERNITY