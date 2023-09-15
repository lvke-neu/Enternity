#pragma warning(disable:4312) 

#include "ScenePanel.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneGraph/3D/Scene3D.h"
#include "Scene/SceneGraph/3D/Node3D.h"
#include "Scene/SceneGraph/Component.h"
#include "Scene/SceneGraph/3D/Visual3DComponent.h"
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
#include <rttr/type>

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

	static Node* selectedNode = nullptr;
	void TreeNode(Node* node)
	{
		if (!node)
		{
			return;
		}

		if (ImGui::TreeNode(node->get_name().c_str()))
		{
			selectedNode = node;

			for (auto child : node->get_childs())
			{
				TreeNode(child);
			}


			if (ImGui::Button("add"))
			{
				Node3D* nodeTmp = new Node3D;
				nodeTmp->set_name(node->get_name() + "_" + std::to_string(node->get_childs().size()));
				nodeTmp->addToParent(node);
			}
			if (node->get_name() != "RootNode")
			{
				if (ImGui::Button("remove"))
				{
					node->removeFromParent();
					delete node;
					node = nullptr;
					selectedNode = nullptr;
				}
			}

			ImGui::TreePop();
		}
	}

	void reflectProperty(const rttr::property& prop)
	{

	}

	void ScenePanel::draw()
	{
		ImGui::Begin("SceneGraph");

		auto rootNode = Engine::GetInstance().getSceneManager()->getCurrentScene()->get_rootNode();
		TreeNode(rootNode);
		
		ImGui::End();


		ImGui::Begin("Node");

		if (selectedNode)
		{
			ImGui::Text("uuid:"); ImGui::SameLine();ImGui::Text(selectedNode->get_uuid().c_str());
			ImGui::Text("name:"); ImGui::SameLine();ImGui::Text(selectedNode->get_name().c_str());
			ImGui::Separator();

			for (const auto& comp : selectedNode->get_components())
			{
				ImGui::PushID(comp->get_uuid().c_str());

				rttr::type type = rttr::type::get_by_name(comp->get_class_name());

				ImGui::Text(("Type:" + type.get_name().to_string()).c_str());
			
				
				for (auto& prop : type.get_properties())
				{
					ImGui::Text((prop.get_name().to_string() + ":").c_str());
					ImGui::SameLine();

					if (prop.get_type().get_name() == "bool")
					{
						bool boolean = prop.get_value(comp).to_bool();

						if (ImGui::Checkbox(prop.get_type().get_name().to_string().c_str(), &boolean))
						{
							prop.set_value(comp, boolean);
						}
					}
					if (prop.get_type().get_name() == "classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char> >")
					{
						std::string str = prop.get_value(comp).to_string();

						char buffer[256];
						memset(buffer, 0, sizeof(buffer));
						memcpy_s(buffer, sizeof(buffer), str.c_str(), sizeof(buffer));
						if (ImGui::InputText(prop.get_type().get_name().to_string().c_str(), buffer, sizeof(buffer)))
						{
							prop.set_value(comp, std::string(buffer));
						}
					}

					if (prop.get_type().is_enumeration())
					{
						//auto type2 = prop.get_type();
						//auto enummm = type2.get_enumeration();
						//for (auto str : enummm.get_names())
						//{
						//	int i = 0;
						//}
						//int i = 0;

						std::vector<std::string> enumString;
						for (const auto& str : prop.get_type().get_enumeration().get_names())
						{
							enumString.emplace_back(str);
						}

						if (ImGui::BeginCombo(prop.get_type().get_name().to_string().c_str(), prop.get_value(comp).to_string().c_str()))
						{
							for (int i = 0; i < enumString.size(); i++)
							{
								bool isSelected = prop.get_value(comp).to_string() == enumString[i];
								if (ImGui::Selectable(enumString[i].c_str(), isSelected))
								{
									prop.set_value(comp, prop.get_type().get_enumeration().name_to_value(enumString[i].c_str()));
								}
							}

							ImGui::EndCombo();
						}
					}

					
				}


				ImGui::Separator();

				ImGui::PopID();
			}

			if (ImGui::Button("add"))
			{
				Component* comp = new Component;
				comp->addToNode(selectedNode);
			}

			if (ImGui::Button("add2"))
			{
				Visual3DComponent* comp = new Visual3DComponent;
				comp->addToNode(selectedNode);
			}
		}

		ImGui::End();
	}
}