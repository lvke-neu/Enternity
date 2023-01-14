/***************************************************************************************
Author: lvke
Date:2023/1/12 20:55
Description:
Scene Hierarchy Panel
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "ECS/Entity/Entity.h"
#include "ECS/Component/Component.h"
#include "Event/ImguiDrawEventManager.h"

BEGIN_ENTERNITY

class SceneHierarchyPanel : public ImguiDrawEvent
{
public:
	SceneHierarchyPanel(entt::registry* registry);
	~SceneHierarchyPanel();

	virtual void ImguiDraw() override;
private:
	void DrawVec3(const std::string& label, glm::vec3& value, const glm::vec3& resetValue = glm::vec3{ 0.0f }, float columnWidth = 100.0f);
	void DrawEntity(Entity entity);
	void DrawComponent();
private:
	entt::registry* m_pSceneRegistry{ nullptr };
	Entity m_SelectedEntity;
};

END_ENTERNITY
