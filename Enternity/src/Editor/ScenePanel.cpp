#include "ScenePanel.h"
#include "Engine/Engine.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/NameComponent.h"
#include "Scene/ECS/PostProcessComponent.h"
#include "Scene/ECS/SkyBoxComponent.h"
#include "Scene/ECS/PBRMaterialComponent.h"
#include "Scene/ECS/PointLightComponent.h"
#include "Graphics/GraphicsSystem.h"
#include "Pick/PickSystem.h"
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

	void DrawSelectedEntity(Entity& entity)
	{
		if (entity.hasComponent<PostProcessComponent>())
		{
			DrawComponent("PostProcessComponent",
				[&]()
				{
					auto& postprocessComponent = entity.getComponent<PostProcessComponent>();

					PostProcessComponent::PostProcessType postprocessType = postprocessComponent.postprocessType;
					const char* bodyTypeString[] = { "None", "Inversion", "Grayscale","Sharpen", "Blur", "EdgeDetection"};
					const char* currentBodyTypeString = bodyTypeString[(int)postprocessType];
					if (ImGui::BeginCombo("PostprocessType", currentBodyTypeString))
					{
						for (int i = 0; i < 6; i++)
						{
							bool isSelected = currentBodyTypeString == bodyTypeString[i];
							if (ImGui::Selectable(bodyTypeString[i], isSelected))
							{
								currentBodyTypeString = bodyTypeString[i];
								postprocessComponent.postprocessType = (PostProcessComponent::PostProcessType)i;
							}
						}
						ImGui::EndCombo();
					}
				});
		}

		if (entity.hasComponent<SkyBoxComponent>())
		{
			DrawComponent("SkyBoxComponent",
				[&]()
				{
					//if (ImGui::InputText("##Path", entity.getComponent<SkyBoxComponent>().textureCubeMapHDR->getPath(), 256));
					//{

					//}
					//ImGui::Text(entity.getComponent<SkyBoxComponent>().texturePath.c_str());
					//if (ImGui::BeginDragDropTarget())
					//{

					//	ImGui::EndDragDropTarget();
					//}
					
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
					ImGui::DragFloat("MoveSpeed", &cameraComponent.moveSpeed, 1.0f, -9999.0f, 9999.0f);
				});
		}

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

		if (entity.hasComponent<PBRMaterialComponent>())
		{
			DrawComponent("PBRMaterialComponent",
				[&]()
				{
					auto& pbrMaterialComponent = entity.getComponent<PBRMaterialComponent>();

					//ImGui::ColorEdit3("Albedo", &pbrMaterialComponent.albedo[0]);
					//ImGui::DragFloat("Metallic", &pbrMaterialComponent.metallic, 0.01f, 0.0f, 1.0f);
					//ImGui::DragFloat("Roughness", &pbrMaterialComponent.roughness, 0.01f, 0.0f, 1.0f);
					//ImGui::DragFloat("Ao", &pbrMaterialComponent.ao, 0.01f, 0.0f, 1.0f);
				});
		}

		if (entity.hasComponent<PointLightComponent>())
		{
			DrawComponent("PointLightComponent",
				[&]()
				{
					auto& pointLightComponent = entity.getComponent<PointLightComponent>();

					DrawVec3("Position", pointLightComponent.position, glm::vec3(0.0f), 0.1);
					DrawVec3("Color", pointLightComponent.color, glm::vec3(1.0f));
				});
		}

		//if (entity.hasComponent<Visual3DComponent>())
		//{
		//	DrawComponent("Visual3DComponent",
		//		[&]()
		//		{
		//			auto& visual3DComponent = entity.getComponent<Visual3DComponent>();

		//			DrawComponent("Mesh",
		//				[&]()
		//				{
		//					
		//					if (visual3DComponent.mesh)
		//					{
		//						ImGui::Text(("Mesh:" + visual3DComponent.mesh->getFullPath()).c_str());
		//					}

		//				});

		//			DrawComponent("Renderer",
		//				[&]()
		//				{
		//					if (visual3DComponent.renderer)
		//					{
		//						ImGui::Text(("VsShader:" + visual3DComponent.renderer->getVsShader()).c_str());
		//						ImGui::Text(("PsShader:" + visual3DComponent.renderer->getPsShader()).c_str());
		//						if (ImGui::Button("ReCompile"))
		//						{
		//							visual3DComponent.renderer->reCompile();
		//						}
		//						DrawComponent("RenderPass",
		//							[&]()
		//							{
		//								RenderPass renderPass = visual3DComponent.renderer->getRenderPass();
		//								const char* bodyTypeString[] = { "Point", "Line", "Fill" };
		//								const char* currentBodyTypeString = bodyTypeString[renderPass.fillMode];
		//								if (ImGui::BeginCombo("FillMode", currentBodyTypeString))
		//								{
		//									for (int i = 0; i < 3; i++)
		//									{
		//										bool isSelected = currentBodyTypeString == bodyTypeString[i];
		//										if (ImGui::Selectable(bodyTypeString[i], isSelected))
		//										{
		//											currentBodyTypeString = bodyTypeString[i];
		//											renderPass.fillMode = (RenderPass::FillMode)i;
		//											visual3DComponent.renderer->setRenderPass(renderPass);
		//										}
		//									}
		//									ImGui::EndCombo();
		//								}

		//								if (ImGui::Checkbox("EnableDepth", &renderPass.enableDepth))
		//								{
		//									visual3DComponent.renderer->setRenderPass(renderPass);
		//								}
		//								if (ImGui::Checkbox("EnableBlend", &renderPass.enableBlend))
		//								{
		//									visual3DComponent.renderer->setRenderPass(renderPass);
		//								}

		//							});								
		//					}
		//				});

		//			DrawComponent("EnableEnvironmentMap",
		//				[&]()
		//				{
		//					Visual3DComponent::EnvironmentMapType environmentMapType = visual3DComponent.environmentMapType;
		//					const char* bodyTypeString[] = { "None", "Reflection", "Refraction" };
		//					const char* currentBodyTypeString = bodyTypeString[(int)environmentMapType];
		//					if (ImGui::BeginCombo("EnableEnvironmentMapType", currentBodyTypeString))
		//					{
		//						for (int i = 0; i < 3; i++)
		//						{
		//							bool isSelected = currentBodyTypeString == bodyTypeString[i];
		//							if (ImGui::Selectable(bodyTypeString[i], isSelected))
		//							{
		//								visual3DComponent.environmentMapType = (Visual3DComponent::EnvironmentMapType)i;
		//							}
		//						}
		//						ImGui::EndCombo();
		//					}
		//				});
		//		});
		//}

		//if (entity.hasComponent<PostprocessComponent>())
		//{
		//	DrawComponent("PostprocessComponent",
		//		[&]()
		//		{
		//			auto& postprocessComponent = entity.getComponent<PostprocessComponent>();

		//			PostprocessComponent::PostprocessType postprocessType = postprocessComponent.postprocessType;
		//			const char* bodyTypeString[] = { "None", "Inversion", "Grayscale","Sharpen", "Blur", "EdgeDetection"};
		//			const char* currentBodyTypeString = bodyTypeString[(int)postprocessType];
		//			if (ImGui::BeginCombo("PostprocessType", currentBodyTypeString))
		//			{
		//				for (int i = 0; i < 6; i++)
		//				{
		//					bool isSelected = currentBodyTypeString == bodyTypeString[i];
		//					if (ImGui::Selectable(bodyTypeString[i], isSelected))
		//					{
		//						currentBodyTypeString = bodyTypeString[i];
		//						postprocessComponent.postprocessType = (PostprocessComponent::PostprocessType)i;
		//					}
		//				}
		//				ImGui::EndCombo();
		//			}
		//		});
		//}

		//if (entity.hasComponent<SkyboxComponent>())
		//{
		//	DrawComponent("SkyboxComponent",
		//		[&]()
		//		{
		//			auto& skyboxComponent = entity.getComponent<SkyboxComponent>();

		//			SkyboxComponent::SkyboxType skyboxType = skyboxComponent.skyboxType;
		//			const char* bodyTypeString[] = { "None", "Default", "Sunset", "Daylight"};
		//			const char* currentBodyTypeString = bodyTypeString[(int)skyboxType];
		//			if (ImGui::BeginCombo("SkyboxType", currentBodyTypeString))
		//			{
		//				for (int i = 0; i < 4; i++)
		//				{
		//					bool isSelected = currentBodyTypeString == bodyTypeString[i];
		//					if (ImGui::Selectable(bodyTypeString[i], isSelected))
		//					{
		//						skyboxComponent.skyboxType = (SkyboxComponent::SkyboxType)i;
		//						if (!isSelected)
		//						{
		//							Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getCubeMapTextureAsyn(SkyboxComponent::FullPaths[skyboxComponent.skyboxType],
		//								[=](CubeMapTexture* cubeMapTexture)
		//								{
		//									auto& comp = entity.getComponent<SkyboxComponent>();
		//									SAFE_DELETE_SET_NULL(comp.cubeMapTexture);
		//									comp.cubeMapTexture = cubeMapTexture;
		//								});
		//						}

		//					}
		//				}
		//				ImGui::EndCombo();
		//			}

		//		});
		//}
	}

	void ScenePanel::draw()
	{
		ImGui::Begin("Entity");

		for (const auto& entity : Engine::GetInstance().getSceneManager()->getCurrentScene()->getEntities())
		{
			ImGui::PushID((int)entity.first);
			if (ImGui::Selectable(entity.second.getComponent<NameComponent>().name.c_str(), 
				Engine::GetInstance().getPickSystem()->getPickEntityId() == (int)entity.first))
			{
				Engine::GetInstance().getPickSystem()->setPickEntityId((int)entity.first);
			}
			ImGui::PopID();
		}
		
		//if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		//{
		//	Engine::GetInstance().getPickSystem()->setPickEntityId(-1);
		//}

		ImGui::End();

		ImGui::Begin("Component");

		Entity selectedEntity = Engine::GetInstance().getSceneManager()->getCurrentScene()->getEntity((entt::entity)Engine::GetInstance().getPickSystem()->getPickEntityId());
		if (selectedEntity.isValidEntity())
		{
			DrawSelectedEntity(selectedEntity);
		}
		
		ImGui::End();
	}
}