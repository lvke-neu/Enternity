#pragma warning(disable:4312) 

#include "ScenePanel.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Scene/SceneManager.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/NameComponent.h"
#include "Scene/ECS/PostProcessComponent.h"
#include "Scene/ECS/SkyBoxComponent.h"
#include "Scene/ECS/PBRMaterialComponent.h"
#include "Scene/ECS/SunLightComponent.h"
#include "Scene/ECS/SkeletonModelComponent.h"
#include "Scene/ECS/StaticModelComponent.h"
#include "Scene/ECS/ModelComponent.h"
#include "Scene/Model/Model.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Pick/PickSystem.h"
#include "Common/Macro.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

namespace Enternity
{
	void DrawVec3(const std::string& label, glm::vec3& value, const glm::vec3& resetValue = glm::vec3{ 0.0f }, float step = 1.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text(label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 0 });

		float lineHeigh = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeigh + 3.0f, lineHeigh };

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
		{
			value.x = resetValue.x;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##X", &value.x, step, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
		{
			value.y = resetValue.y;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Y", &value.y, step, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.3f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
		{
			value.z = resetValue.z;
		}
		ImGui::PopFont();
		ImGui::PopStyleColor(3);
		ImGui::SameLine();
		ImGui::DragFloat("##Z", &value.z, step, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();


		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();
	}

	void DrawComponent(const std::string& name, std::function<void()> uiFunction)
	{
		ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;

		ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4,4 });
		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImGui::Separator();

		bool b_IsOpen = ImGui::TreeNodeEx(name.c_str(), treeNodeFlags);

		ImGui::PopStyleVar();


		if (b_IsOpen)
		{
			uiFunction();
			ImGui::TreePop();
		}
		
	}



	void ScenePanel::draw()
	{
		ImGui::Begin("Entity");

		//for (const auto& entity : Engine::GetInstance().getSceneManager()->getCurrentScene()->getEntities())
		//{
		//	ImGui::PushID((int)entity.first);
		//	if (ImGui::Selectable(entity.second.getComponent<NameComponent>().name.c_str(), 
		//		Engine::GetInstance().getPickSystem()->getPickEntityId() == (int)entity.first))
		//	{
		//		Engine::GetInstance().getPickSystem()->setPickEntityId((int)entity.first);
		//	}
		//	ImGui::PopID();
		//}
		//
		////if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		////{
		////	Engine::GetInstance().getPickSystem()->setPickEntityId(-1);
		////}

		//ImGui::End();

		//ImGui::Begin("Component");

		//Entity selectedEntity = Engine::GetInstance().getSceneManager()->getCurrentScene()->getEntity((entt::entity)Engine::GetInstance().getPickSystem()->getPickEntityId());
		//if (selectedEntity.isValidEntity())
		//{
		//	DrawSelectedEntity(selectedEntity);
		//}
		
		ImGui::End();
	}
}