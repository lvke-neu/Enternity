#include "SceneHierarchyPanel.h"
#include "SceneManager.h"
#include "Log/Log.h"

BEGIN_ENTERNITY

SceneHierarchyPanel::SceneHierarchyPanel()
{
	ImguiDrawEventManager::GetInstance().RegisterEvent(this);
}

SceneHierarchyPanel::~SceneHierarchyPanel()
{
	ImguiDrawEventManager::GetInstance().UnRegisterEvent(this);
}

void SceneHierarchyPanel::ImguiDraw()
{
	ImGui::Begin("Scene Hierarchy panel");
	//traversal all entity in one registry
	DrawEntity(SceneManager::GetInstance().m_MainCameraEntity, false);
	for (auto& entity : SceneManager::GetInstance().m_Entities)
	{
		DrawEntity(entity.second);
	}

	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		m_SelectedEntity = {};

	//add entity
	if (ImGui::BeginPopupContextWindow(0, 1, false))
	{
		if (ImGui::MenuItem("Create Entity"))
		{
			Entity cubeEntity(&SceneManager::GetInstance().m_Registry);
			SceneManager::GetInstance().m_Entities.insert({ cubeEntity.GetEntityUid(), cubeEntity });
		}
		ImGui::EndPopup();
	}

	ImGui::End();


	ImGui::Begin("Entity Property");
	DrawComponentOfSelectedEntity();
	ImGui::End();

	ImGui::Begin("Stats");
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

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

void SceneHierarchyPanel::DrawEntity(Entity entity, bool allowedDelete)
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
				SceneManager::GetInstance().m_Entities.erase(entity.GetEntityUid());
				entity.Destroy();
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
	if (m_SelectedEntity.IsValidEntity() && m_SelectedEntity != SceneManager::GetInstance().m_MainCameraEntity && ImGui::Button("Add Component"))
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
			m_SelectedEntity.AddComponent<MaterialComponent>();
			ImGui::CloseCurrentPopup();
		}

		if (ImGui::MenuItem("MotorComponent"))
		{
			m_SelectedEntity.AddComponent<MotorComponent>();
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
				meshComponent.LoadMesh(buffer);
			}

		}
	);
	

	//material component
	DrawComponent<MaterialComponent>("MaterialComponent",
		[&]()
		{
			auto& materialComponent = m_SelectedEntity.GetComponent<MaterialComponent>();

			if (ImGui::Checkbox("UseColor", &materialComponent.m_bUseColor))
			{
				materialComponent.SetIsUseColor(materialComponent.m_bUseColor);
			}

			if (ImGui::ColorEdit4("BaseColor", &materialComponent.m_BaseColor[0]))
			{
				materialComponent.SetBaseColor(materialComponent.m_BaseColor);
			}

			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			memcpy_s(buffer, sizeof(buffer), materialComponent.m_TextureFilePath.c_str(), sizeof(buffer));
			if (ImGui::InputText("TextureFilePath", buffer, sizeof(buffer)))
			{
				materialComponent.LoadTexture(buffer);
			}
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

