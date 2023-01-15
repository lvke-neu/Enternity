/***************************************************************************************
Author: lvke
Date:2023/1/12 20:55
Description:
Scene Hierarchy Panel
****************************************************************************************/
#pragma once

#include "Macro/Macro.h"
#include "SceneManager.h"
#include <functional>
#include "Imgui/ImguiManager.h"
#include "Event/ImguiDrawEventManager.h"

BEGIN_ENTERNITY

class SceneHierarchyPanel : public ImguiDrawEvent
{
public:
	SceneHierarchyPanel();
	~SceneHierarchyPanel();

	virtual void ImguiDraw() override;
	void SetSelectedEntityNull()
	{
		m_SelectedEntity = {};
	}
private:
	void DrawVec3(const std::string& label, glm::vec3& value, const glm::vec3& resetValue = glm::vec3{ 0.0f }, float columnWidth = 100.0f);
	void DrawEntity(Entity entity, bool allowedDelete = true);
	void DrawComponentOfSelectedEntity();

	

	template<typename T>
	void DrawComponent(const std::string& name, std::function<void()> uiFunction, bool allowedRemove = true)
	{
		if (m_SelectedEntity.HasComponent<T>())
		{
			ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4,4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y*2.0f;
			ImGui::Separator();

			bool b_IsOpen = ImGui::TreeNodeEx(name.c_str(), treeNodeFlags);

			ImGui::PopStyleVar();


			bool b_ClickRemove = false;
			if (allowedRemove)
			{
				ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
				if (ImGui::Button("+", { lineHeight, lineHeight }))
				{
					ImGui::OpenPopup("ComponentSettings");
				}

				if (ImGui::BeginPopup("ComponentSettings"))
				{
					if (ImGui::MenuItem("Remove Component"))
					{
						b_ClickRemove = true;
					}

					ImGui::EndPopup();
				}
			}

			if (b_IsOpen)
			{
				uiFunction();
				ImGui::TreePop();
			}

			if(b_ClickRemove)
				m_SelectedEntity.RemoveComponent<T>();
		}
	}
private:
	Entity m_SelectedEntity;
};

END_ENTERNITY
