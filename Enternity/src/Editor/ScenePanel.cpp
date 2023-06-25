#include "ScenePanel.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Engine/Engine.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/Visual3DComponent.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/NameComponent.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Renderer/Renderer.h"

namespace Enternity
{
	void DrawVec3(const std::string& label, glm::vec3& value, const glm::vec3& resetValue = glm::vec3{ 0.0f }, float columnWidth = 100.0f)
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
		ImGui::DragFloat("##X", &value.x, 1.0f, 0.0f, 0.0f, "%.2f");
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
		ImGui::DragFloat("##Y", &value.y, 1.0f, 0.0f, 0.0f, "%.2f");
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
		ImGui::DragFloat("##Z", &value.z, 1.0f, 0.0f, 0.0f, "%.2f");
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

	void DrawSelectedEntity(Entity& entity)
	{
		if (entity.hasComponent<TransformComponent>())
		{
			DrawComponent("TransformComponent",
				[&]()
				{
					auto& transformComponent = entity.getComponent<TransformComponent>();
					auto& translation = transformComponent.translation;
					auto& rotation = transformComponent.rotation;
					auto& scale = transformComponent.scale;

					DrawVec3("Translation", translation, glm::vec3(0.0f));
					DrawVec3("Rotation", rotation, glm::vec3(0.0f));
					DrawVec3("Scale", scale, glm::vec3(1.0f));
				});
		}

		if (entity.hasComponent<CameraComponent>())
		{
			DrawComponent("CameraComponent",
				[&]()
				{
					auto& cameraComponent = entity.getComponent<CameraComponent>();
					ImGui::DragFloat("FovY", &cameraComponent.fovy, 1.0f, -9999.0f, 9999.0f);
					ImGui::DragFloat("Aspect", &cameraComponent.aspect, 1.0f, -9999.0f, 9999.0f);
					ImGui::DragFloat("NearZ", &cameraComponent.nearZ, 1.0f, -9999.0f, 9999.0f);
					ImGui::DragFloat("FarZ", &cameraComponent.farZ, 1.0f, -9999.0f, 9999.0f);

				});
		}

		if (entity.hasComponent<Visual3DComponent>())
		{
			DrawComponent("Visual3DComponent",
				[&]()
				{
					auto& visual3DComponent = entity.getComponent<Visual3DComponent>();

					DrawComponent("Mesh",
						[&]()
						{
							
							if (visual3DComponent.mesh)
							{
								ImGui::Text(("Mesh:" + visual3DComponent.mesh->getFullPath()).c_str());
							}

						});

					DrawComponent("Renderer",
						[&]()
						{
							if (visual3DComponent.renderer)
							{
								ImGui::Text(("VsShader:" + visual3DComponent.renderer->getVsShader()).c_str());
								ImGui::Text(("PsShader:" + visual3DComponent.renderer->getPsShader()).c_str());
								if (ImGui::Button("ReCompile"))
								{
									visual3DComponent.renderer->reCompile();
								}
								DrawComponent("RenderPass",
									[&]()
									{

										RenderPass renderPass = visual3DComponent.renderer->getRenderPass();
										const char* bodyTypeString[] = { "Point", "Line", "Fill" };
										const char* currentBodyTypeString = bodyTypeString[renderPass.fillMode];
										if (ImGui::BeginCombo("FillMode", currentBodyTypeString))
										{
											for (int i = 0; i < 3; i++)
											{
												bool isSelected = currentBodyTypeString == bodyTypeString[i];
												if (ImGui::Selectable(bodyTypeString[i], isSelected))
												{
													currentBodyTypeString = bodyTypeString[i];
													renderPass.fillMode = (FillMode)i;
													visual3DComponent.renderer->setRenderPass(renderPass);
												}
												if (isSelected)
													ImGui::SetItemDefaultFocus();
											}
											ImGui::EndCombo();
										}

										if (ImGui::Checkbox("EnableDepth", &renderPass.enableDepth))
										{
											visual3DComponent.renderer->setRenderPass(renderPass);
										}

									});								
							}
						});
					
				});
		}
	}

	void ScenePanel::draw()
	{
		ImGui::Begin("Entity");

		for (const auto& entity : Engine::GetInstance().getSceneManager()->getCurrentScene()->m_entities)
		{
			ImGui::PushID((int)entity.first);
			if (ImGui::Selectable(entity.second.getComponent<NameComponent>().name.c_str(), m_selectedEntityId == (int)entity.first))
			{
				m_selectedEntityId = (int)entity.first;
			}
			ImGui::PopID();
		}
		
		if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
			m_selectedEntityId = -1;

		ImGui::End();
		
		//for (const auto& entity : Engine::GetInstance().getSceneManager()->getCurrentScene()->m_entities)
		//{
		//	ImGui::Text(std::to_string((int)entity.first).c_str());

		//	if (entity.second.hasComponent<CameraComponent>())
		//	{
		//		ImGui::Text("Camera Frustum");
		//	}

		//	if (entity.second.hasComponent<TransformComponent>())
		//	{
		//		auto& transformComponent = entity.second.getComponent<TransformComponent>();
		//		auto& translation = transformComponent.translation;
		//		auto& rotation = transformComponent.rotation;
		//		auto& scale = transformComponent.scale;

		//		ImGui::PushID((int)entity.first);
		//		DrawVec3("Translation", translation, glm::vec3(0.0f));
		//		DrawVec3("Rotation", rotation, glm::vec3(0.0f));
		//		DrawVec3("Scale", scale, glm::vec3(1.0f));
		//		ImGui::PopID();
		//	}
		//	
		//	if (entity.second.hasComponent<Visual3DComponent>())
		//	{
		//		auto& v3d = entity.second.getComponent<Visual3DComponent>();
		//		if (v3d.mesh)
		//		{
		//			ImGui::Text(("Mesh:" + v3d.mesh->getFullPath()).c_str());
		//		}
		//	}	

		//	ImGui::Separator();
		//}
		ImGui::Begin("Component");

		if (m_selectedEntityId != -1)
		{
			auto& selectedEntity = Engine::GetInstance().getSceneManager()->getCurrentScene()->m_entities[(entt::entity)m_selectedEntityId];
			DrawSelectedEntity(selectedEntity);
		}

		ImGui::End();
	}
}