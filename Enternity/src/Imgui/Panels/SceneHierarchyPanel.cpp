#include "SceneHierarchyPanel.h"
#include "Scene/SceneManager.h"
#include "Log/Log.h"

BEGIN_ENTERNITY

SceneHierarchyPanel::SceneHierarchyPanel() : IPanel()
{
	
}

SceneHierarchyPanel::~SceneHierarchyPanel()
{
	
}

void SceneHierarchyPanel::ImguiDraw()
{
	ImGui::Begin("Scene Hierarchy panel");
	//traversal all entity in one registry

	bool needDelete = false;
	DrawEntity(SceneManager::GetInstance().m_EditorCameraEntity, needDelete, false);
	DrawEntity(SceneManager::GetInstance().m_PlayerCameraEntity, needDelete, false);
	DrawEntity(SceneManager::GetInstance().m_DirectionLightEntity, needDelete, false);
	ImGui::Separator();
	
	std::vector<Entity> needDeletedEntity;
	for (auto& entity : SceneManager::GetInstance().m_Entities)
	{
		needDelete = false;
		DrawEntity(entity.second, needDelete);
		if (needDelete)
			needDeletedEntity.push_back(entity.second);
	}

	for (auto& entity : needDeletedEntity)
	{
		SceneManager::GetInstance().m_Entities.erase(entity.GetEntityUid());
		entity.Destroy();
	}


	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		m_SelectedEntity = {};

	//add entity
	if (ImGui::BeginPopupContextWindow(0, 1, false))
	{
		if (ImGui::MenuItem("Create Entity"))
		{
			Entity entity(&SceneManager::GetInstance().m_Registry);
			SceneManager::GetInstance().m_Entities.insert({ entity.GetEntityUid(), entity });
		}
		ImGui::EndPopup();
	}

	ImGui::End();


	ImGui::Begin("Entity Property");
	DrawComponentOfSelectedEntity();
	ImGui::End();
}

void SceneHierarchyPanel::SetSelectedEntity(int entityId)
{
	if (entityId == -1)
	{
		m_SelectedEntity = {};
	}
	else if (entityId >= 0)
	{
		m_SelectedEntity = Entity(&SceneManager::GetInstance().m_Registry, (entt::entity)entityId);
	}
}

void SceneHierarchyPanel::DrawVec3(const std::string & label, glm::vec3 & value, const glm::vec3 & resetValue, float columnWidth)
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

void SceneHierarchyPanel::DrawEntity(Entity entity, bool& needDelete, bool allowedDelete)
{
	auto& tagComponent = entity.GetComponent<TagComponent>();

	if (ImGui::Selectable((tagComponent.m_Tag + " ").c_str(), m_SelectedEntity == entity))
	{
		LOG_INFO("select " + entity.GetComponent<TagComponent>().m_Tag);
		m_SelectedEntity = entity;
	}

	//delete entity
	if (allowedDelete && ImGui::BeginPopupContextItem())
	{
		if (ImGui::MenuItem("Delete Entity"))
		{
			if (SceneManager::GetInstance().m_Entities.find(entity.GetEntityUid()) != SceneManager::GetInstance().m_Entities.end())
			{
				if(m_SelectedEntity == entity)
					m_SelectedEntity = {};

				needDelete = true;
			}
		}
		ImGui::EndPopup();
	}
}

void SceneHierarchyPanel::DrawComponentOfSelectedEntity()
{
	if (!m_SelectedEntity.IsValidEntity())
		return;

	//tag component
	if (m_SelectedEntity.HasComponent<TagComponent>())
	{
		auto& tagComponent = m_SelectedEntity.GetComponent<TagComponent>();
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		memcpy_s(buffer, sizeof(buffer), tagComponent.m_Tag.c_str(), sizeof(buffer));
		if (ImGui::InputText("##Name", buffer, sizeof(buffer)))
		{
			tagComponent.m_Tag = buffer;
		}
	}


	//add component
	ImGui::SameLine();
	ImGui::PushItemWidth(-1);
	if (m_SelectedEntity.IsValidEntity()
		&& m_SelectedEntity != SceneManager::GetInstance().m_EditorCameraEntity 
		&& ImGui::Button("Add Component")
		&& m_SelectedEntity != SceneManager::GetInstance().m_PlayerCameraEntity
		&& m_SelectedEntity !=SceneManager::GetInstance().m_DirectionLightEntity)
	{
		ImGui::OpenPopup("AddComponent");
	}
	if (ImGui::BeginPopup("AddComponent"))
	{
		if (ImGui::MenuItem("TransformComponent"))
		{
			m_SelectedEntity.AddComponent<TransformComponent>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("MeshComponent"))
		{
			m_SelectedEntity.AddComponent<MeshComponent>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("MaterialComponent"))
		{
			m_SelectedEntity.AddComponent<MaterialComponent>().LoadShader();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("MotorComponent"))
		{
			m_SelectedEntity.AddComponent<MotorComponent>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("RigidBody2DComponent"))
		{
			m_SelectedEntity.AddComponent<RigidBody2DComponent>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("BoxCollider2DComponent"))
		{
			m_SelectedEntity.AddComponent<BoxCollider2DComponent>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("RigidBodyComponent"))
		{
			m_SelectedEntity.AddComponent<RigidBodyComponent>();
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
	ImGui::PopItemWidth();

	//transform component
	bool allowedRemove = !m_SelectedEntity.HasComponent<CameraComponent>();
	DrawComponent<TransformComponent>("TransformComponent",
		[&]()
		{
			auto& transformComponent = m_SelectedEntity.GetComponent<TransformComponent>();
			auto& translation = transformComponent.m_Translation;
			auto& rotation = transformComponent.m_Rotation;
			auto& scale = transformComponent.m_Scale;

			DrawVec3("Translation", translation, glm::vec3(0.0f));
			glm::vec3 angleRotation = glm::degrees(rotation);
			DrawVec3("Rotation", angleRotation, glm::vec3(0.0f));
			rotation = glm::radians(angleRotation);
			DrawVec3("Scale", scale, glm::vec3(1.0f));
		}, allowedRemove);
	

	//mesh component
	DrawComponent<MeshComponent>("MeshComponent",
		[&]()
		{
			auto& meshComponent = m_SelectedEntity.GetComponent<MeshComponent>();
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			memcpy_s(buffer, sizeof(buffer), meshComponent.m_MeshFilePath.c_str(), sizeof(buffer));
			if (ImGui::InputText("MeshFilePath", buffer, sizeof(buffer)))
			{
				meshComponent.m_MeshFilePath = buffer;
				meshComponent.Load();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
				{
					LOG_INFO((char*)payload->Data);
					std::string path((char*)payload->Data);
					path = path.substr(0, payload->DataSize);
					meshComponent.m_MeshFilePath = path;
					meshComponent.Load();
				}
				ImGui::EndDragDropTarget();
			}

		}
	);
	

	//material component
	DrawComponent<MaterialComponent>("MaterialComponent",
		[&]()
		{
			auto& materialComponent = m_SelectedEntity.GetComponent<MaterialComponent>();

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			memcpy_s(buffer, sizeof(buffer), materialComponent.m_DiffuseTextureFilePath.c_str(), sizeof(buffer));
			if (ImGui::InputText("DiffuseTextureFilePath", buffer, sizeof(buffer)))
			{
				materialComponent.m_DiffuseTextureFilePath = buffer;
				materialComponent.LoadDiffuseTexture();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
				{
					LOG_INFO((char*)payload->Data);
					std::string path((char*)payload->Data);
					path = path.substr(0, payload->DataSize);
					materialComponent.m_DiffuseTextureFilePath = path;
					materialComponent.LoadDiffuseTexture();
				}
				ImGui::EndDragDropTarget();
			}

			memset(buffer, 0, sizeof(buffer));
			memcpy_s(buffer, sizeof(buffer), materialComponent.m_SpecularTextureFilePath.c_str(), sizeof(buffer));
			if (ImGui::InputText("SpecularTextureFilePath", buffer, sizeof(buffer)))
			{
				materialComponent.m_SpecularTextureFilePath = buffer;
				materialComponent.LoadSpecularTexture();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
				{
					LOG_INFO((char*)payload->Data);
					std::string path((char*)payload->Data);
					path = path.substr(0, payload->DataSize);
					materialComponent.m_SpecularTextureFilePath = path;
					materialComponent.LoadSpecularTexture();
				}
				ImGui::EndDragDropTarget();
			}


			ImGui::Text("ShaderFilePath:%s", materialComponent.m_ShaderFilePath.c_str());


			if (ImGui::Checkbox("UseTexture", &materialComponent.m_UseTexture))
			{
				materialComponent.SetUseTexture();
			}

			ImGui::Separator();
			ImGui::ColorEdit4("Ambient",  &materialComponent.m_Ambient[0]);
			ImGui::ColorEdit4("Diffuse",  &materialComponent.m_Diffuse[0]);
			ImGui::ColorEdit4("Specular", &materialComponent.m_Specular[0]);
			ImGui::DragFloat("Shininess", &materialComponent.m_Shininess, 1.0f, 1.0f, 9999.0f);
		}
	);
	
	//motor component
	DrawComponent<MotorComponent>("MotorComponent",
		[&]()
		{
			auto& motorComponent = m_SelectedEntity.GetComponent<MotorComponent>();
			ImGui::DragFloat("RotationXAnglePerSecond", &motorComponent.m_RotationXAnglePerSecond, 1.0f);
			ImGui::DragFloat("RotationYAnglePerSecond", &motorComponent.m_RotationYAnglePerSecond, 1.0f);
		});

	//RigidBody2DComponent
	DrawComponent<RigidBody2DComponent>("RigidBody2DComponent",
		[&]()
		{
			auto& rb2dc = m_SelectedEntity.GetComponent<RigidBody2DComponent>();
			const char* bodyTypeString[] = { "Static", "Kinematic", "Dynamic" };
			const char* currentBodyTypeString = bodyTypeString[(int)rb2dc.m_BodyType];

			if (ImGui::BeginCombo("BodyType", currentBodyTypeString))
			{
				for (int i = 0; i < 3; i++)
				{
					bool isSelected = currentBodyTypeString == bodyTypeString[i];
					if (ImGui::Selectable(bodyTypeString[i], isSelected))
					{
						currentBodyTypeString = bodyTypeString[i];
						rb2dc.m_BodyType = (RigidBody2DComponent::BodyType)i;
					}
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			ImGui::Checkbox("FixedRotation", &rb2dc.m_FixedRotation);		
		});

	//BoxCollider2DComponent
	DrawComponent<BoxCollider2DComponent>("BoxCollider2DComponent",
		[&]()
		{
			auto& bc2dc = m_SelectedEntity.GetComponent<BoxCollider2DComponent>();
			ImGui::DragFloat2("Offset", &bc2dc.m_Offset.x);
			ImGui::DragFloat2("Size", &bc2dc.m_Size.x);
			ImGui::DragFloat("Density", &bc2dc.m_Density, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Friction", &bc2dc.m_Friction, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution", &bc2dc.m_Restitution, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("RestitutionThreshold", &bc2dc.m_RestitutionThreshold, 0.01f, 0.0f);
		});

	//RigidBodyComponent
	DrawComponent<RigidBodyComponent>("RigidBodyComponent",
		[&]()
		{	auto& rbc = m_SelectedEntity.GetComponent<RigidBodyComponent>();
			
			const char* bodyTypeString[] = { "Box", "Sphere"};
			const char* currentBodyTypeString = bodyTypeString[(int)rbc.m_ColliderShape];

			if (ImGui::BeginCombo("ColliderShape", currentBodyTypeString))
			{
				for (int i = 0; i < 2; i++)
				{
					bool isSelected = currentBodyTypeString == bodyTypeString[i];
					if (ImGui::Selectable(bodyTypeString[i], isSelected))
					{
						currentBodyTypeString = bodyTypeString[i];
						rbc.m_ColliderShape = (RigidBodyComponent::ColliderShape)i;
					}
					if (isSelected)
						ImGui::SetItemDefaultFocus();
				}

				ImGui::EndCombo();
			}

			if (currentBodyTypeString == bodyTypeString[0])
			{
				DrawVec3("Offset", rbc.m_Offset, glm::vec3(0.0f));
			}

			if (currentBodyTypeString == bodyTypeString[1])
			{
				ImGui::DragFloat("Radius", &rbc.m_Radius, 1.0f, 0.0f, FLT_MAX);
			}

			ImGui::Checkbox("ShowColliderShape", &rbc.m_ShowColliderShape);
			ImGui::DragFloat("Mass", &rbc.m_Mass, 1.0f, 0.0f, FLT_MAX);
			ImGui::DragFloat("Friction", &rbc.m_Friction, 0.01f, 0.0f, 1.0f);
			ImGui::DragFloat("Restitution", &rbc.m_Restitution, 0.01f, 0.0f, 1.0f);
			
		});

	//camera component
	DrawComponent<CameraComponent>("CameraComponent",
		[&]()
		{
			auto& cameraComponent = m_SelectedEntity.GetComponent<CameraComponent>();
			ImGui::DragFloat("MoveSpeed", &cameraComponent.m_MoveSpeed, 1.0f, 0.0f, 9999.0f);

			if (ImGui::DragFloat("FovY", &cameraComponent.m_Fovy, 1.0f, -9999.0f, 9999.0f) ||
				ImGui::DragFloat("Aspect", &cameraComponent.m_Aspect, 1.0f, -9999.0f, 9999.0f) ||
				ImGui::DragFloat("NearZ", &cameraComponent.m_NearZ, 1.0f, -9999.0f, 9999.0f) ||
				ImGui::DragFloat("FarZ", &cameraComponent.m_FarZ, 1.0f, -9999.0f, 9999.0f))
			{
				cameraComponent.ReCalculateProjectMatrix();
			}

			if (ImGui::Checkbox("Wireframe", &cameraComponent.m_EnableWireframe))
			{
				if (cameraComponent.m_EnableWireframe)
				{
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				}
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}, false);
	
}


END_ENTERNITY

