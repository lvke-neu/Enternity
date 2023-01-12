/***************************************************************************************
Author: lvke
Date:2023/1/12 20:55
Description:
Scene Hierarchy Panel
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "ECS/Entity/Entity.h"
#include "Event/ImguiDrawEventManager.h"

BEGIN_ENTERNITY

class SceneHierarchyPanel : public ImguiDrawEvent
{
public:
	SceneHierarchyPanel(entt::registry* registry);
	~SceneHierarchyPanel();

	virtual void ImguiDraw() override;
private:
	entt::registry* m_pSceneRegistry{ nullptr };
};

END_ENTERNITY
