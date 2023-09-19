#pragma warning(disable:4312) 

#include "ScenePanel.h"
#include "Engine/Engine.h"
#include "Engine/Node.h"
#include "Engine/Scene.h"
#include "Engine/Component.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneGraph/Transform3D.h"
#include "Graphics/Color.h"
#include "Graphics/Material.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include <glm/vec3.hpp>
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
	static void TreeNode(Node* node)
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


			//if (ImGui::Button("add"))
			//{
			//	Node3D* nodeTmp = new Node3D;
			//	nodeTmp->set_name(node->get_name() + "_" + std::to_string(node->get_childs().size()));
			//	nodeTmp->addToParent(node);
			//}
			//if (node->get_name() != "RootNode")
			//{
			//	if (ImGui::Button("remove"))
			//	{
			//		node->removeFromParent();
			//		delete node;
			//		node = nullptr;
			//		selectedNode = nullptr;
			//	}
			//}

			ImGui::TreePop();
		}
	}

	static void reflect(Reference* reference)
	{
		rttr::type type = rttr::type::get_by_name(reference->get_class_name());

		ImGui::Text(("Type:" + type.get_name().to_string()).c_str());


		if (ImGui::BeginTable(("##" + reference->get_uuid()).c_str(), 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
		{
			ImGui::TableSetupColumn("Property", ImGuiTableColumnFlags_WidthFixed);
			ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthStretch);
			ImGui::TableHeadersRow();

			int index = 0;
			for (auto& prop : type.get_properties())
			{
				ImGui::TableNextRow();

				ImGui::TableSetColumnIndex(0);
				ImGui::Text((prop.get_name().to_string() + ":").c_str());

				ImGui::TableSetColumnIndex(1);

				if (prop.get_type().get_name() == "bool")
				{
					bool boolean = prop.get_value(reference).to_bool();

					if (ImGui::Checkbox(("##" + reference->get_uuid() + std::to_string(index)).c_str(), &boolean))
					{
						prop.set_value(reference, boolean);
					}
				}

				if (prop.get_type().get_name() == "classstd::basic_string<char,structstd::char_traits<char>,classstd::allocator<char> >")
				{
					std::string str = prop.get_value(reference).to_string();

					char buffer[256];
					memset(buffer, 0, sizeof(buffer));
					memcpy_s(buffer, sizeof(buffer), str.c_str(), sizeof(buffer));
					if (ImGui::InputText(("##" + reference->get_uuid() + std::to_string(index)).c_str(), buffer, sizeof(buffer)))
					{
						prop.set_value(reference, std::string(buffer));
					}
				}

				if (prop.get_type().is_enumeration())
				{
					std::vector<std::string> enumString;
					for (const auto& str : prop.get_type().get_enumeration().get_names())
					{
						enumString.emplace_back(str);
					}

					if (ImGui::BeginCombo(("##" + reference->get_uuid() + std::to_string(index)).c_str(), prop.get_value(reference).to_string().c_str()))
					{
						for (int i = 0; i < enumString.size(); i++)
						{
							bool isSelected = prop.get_value(reference).to_string() == enumString[i];
							if (ImGui::Selectable(enumString[i].c_str(), isSelected))
							{
								prop.set_value(reference, prop.get_type().get_enumeration().name_to_value(enumString[i].c_str()));
							}
						}

						ImGui::EndCombo();
					}
				}

				if (prop.get_type().get_name() == "float")
				{
					float value = prop.get_value(reference).to_float();

					if (ImGui::DragFloat(("##" + reference->get_uuid() + std::to_string(index)).c_str(), &value))
					{
						prop.set_value(reference, value);
					}
				}

				if (prop.get_type().get_name() == "Transform3D")
				{
					Transform3D transform3D = prop.get_value(reference).get_value<Transform3D>();
					glm::vec3 translation = transform3D.get_translation();
					glm::vec3 rotation = transform3D.get_rotation();
					glm::vec3 scale = transform3D.get_scale();

					DrawVec3(("##trans" + reference->get_uuid() + std::to_string(index)).c_str(), translation);
					DrawVec3(("##rot" + reference->get_uuid() + std::to_string(index)).c_str(), rotation);
					DrawVec3(("##sca" + reference->get_uuid() + std::to_string(index)).c_str(), scale);

					transform3D.set_translation(translation);
					transform3D.set_rotation(rotation);
					transform3D.set_scale(scale);

					prop.set_value(reference, transform3D);
					
				}

				if (prop.get_type().get_name() == "Color")
				{
					Color color = prop.get_value(reference).get_value<Color>();
					ImGui::ColorEdit4(("##" + reference->get_uuid() + std::to_string(index)).c_str(), color.toPointer());
					
					prop.set_value(reference, color);
				}

				if (prop.get_type().get_name() == "Material")
				{
					Material material = prop.get_value(reference).get_value<Material>();
					reflect(&material);
					prop.set_value(reference, material);
				}

				index++;
			}

			ImGui::EndTable();
		}

		ImGui::Separator();
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
			reflect(selectedNode);

			for (const auto& comp : selectedNode->get_components())
			{
				reflect(comp);
			}

			//if (ImGui::Button("add"))
			//{
			//	Component* comp = new Component;
			//	comp->addToNode(selectedNode);
			//}
			//
			//if (ImGui::Button("add2"))
			//{
			//	Visual3DComponent* comp = new Visual3DComponent;
			//	comp->addToNode(selectedNode);
			//}
			//if (ImGui::Button("add3"))
			//{
			//	Camera3DComponent* comp = new Camera3DComponent;
			//	comp->addToNode(selectedNode);
			//}
		}

		ImGui::End();
	}
}