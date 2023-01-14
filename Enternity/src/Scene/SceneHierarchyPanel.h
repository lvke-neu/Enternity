/***************************************************************************************
Author: lvke
Date:2023/1/12 20:55
Description:
Scene Hierarchy Panel
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "SceneManager.h"
#include "Event/ImguiDrawEventManager.h"

BEGIN_ENTERNITY

class SceneHierarchyPanel : public ImguiDrawEvent
{
public:
	SceneHierarchyPanel();
	~SceneHierarchyPanel();

	virtual void ImguiDraw() override;
private:
	void DrawVec3(const std::string& label, glm::vec3& value, const glm::vec3& resetValue = glm::vec3{ 0.0f }, float columnWidth = 100.0f);
	void DrawEntity(Entity entity, bool allowedDelete = true);
	void DrawComponent();
private:
	Entity m_SelectedEntity;
};

END_ENTERNITY
