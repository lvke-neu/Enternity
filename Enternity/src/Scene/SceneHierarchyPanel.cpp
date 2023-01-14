#include "SceneHierarchyPanel.h"
#include "Imgui/ImguiManager.h"
#include "Log/Log.h"


BEGIN_ENTERNITY

SceneHierarchyPanel::SceneHierarchyPanel(entt::registry* registry):
	m_pSceneRegistry(registry)
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
	m_pSceneRegistry->each(
		[&](entt::entity entityUid)
		{
			Entity entity(m_pSceneRegistry, entityUid);
			DrawEntity(entity);
		}
	);


	if (ImGui::IsMouseDown(0) && ImGui::IsWindowHovered())
		m_SelectedEntity = {};

	ImGui::End();


	ImGui::Begin("Entity Property");
	DrawComponent();
	ImGui::End();

	ImGui::Begin("Stats");

	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

}

void SceneHierarchyPanel::DrawVec3(const std::string & label, glm::vec3 & value, const glm::vec3 & resetValue, float columnWidth)
{
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
	if (ImGui::Button("X", buttonSize))
	{
		value.x = resetValue.x;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	ImGui::DragFloat("##X", &value.x, 1.0f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.7f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.3f, 0.8f, 0.3f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.2f, 0.7f, 0.2f, 1.0f });
	if (ImGui::Button("Y", buttonSize))
	{
		value.y = resetValue.y;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	ImGui::DragFloat("##Y", &value.y, 1.0f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.25f, 0.8f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.3f, 0.2f, 1.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1f, 0.25f, 0.8f, 1.0f });
	if (ImGui::Button("Z", buttonSize))
	{
		value.z = resetValue.z;
	}
	ImGui::PopStyleColor(3);
	ImGui::SameLine();
	ImGui::DragFloat("##Z", &value.z, 1.0f, 0.0f, 0.0f, "%.2f");
	ImGui::PopItemWidth();


	ImGui::PopStyleVar();
	ImGui::Columns(1);

	ImGui::PopID();
}

void SceneHierarchyPanel::DrawEntity(Entity entity)
{
	auto& tagComponent = entity.GetComponent<TagComponent>();

	if (ImGui::Selectable((tagComponent.m_Tag + " ").c_str(), m_SelectedEntity == entity))
	{
		LOG_INFO("select " + entity.GetComponent<TagComponent>().m_Tag);
		m_SelectedEntity = entity;
	}
}

void SceneHierarchyPanel::DrawComponent()
{
	if (!m_SelectedEntity.IsValidEntity())
		return;

	//auto& tagComponent = m_SelectedEntity.GetComponent<TagComponent>();
	//if (ImGui::TreeNode(std::to_string(m_SelectedEntity.GetEntityUid()).c_str(), tagComponent.m_Tag.c_str()))
	//{
	//	ImGui::TreePop();
	//}

	//tag component
	if (m_SelectedEntity.HasComponent<TagComponent>())
	{
		auto& tagComponent = m_SelectedEntity.GetComponent<TagComponent>();
		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		memcpy_s(buffer, sizeof(buffer), tagComponent.m_Tag.c_str(), sizeof(buffer));
		if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		{
			tagComponent.m_Tag = buffer;
		}
	}

	//transform component
	if (m_SelectedEntity.HasComponent<TransformComponent>())
	{
		if (ImGui::TreeNode("TransformComponent"))
		{
			auto& transformComponent = m_SelectedEntity.GetComponent<TransformComponent>();
			auto& translation = transformComponent.m_Translation;
			auto& rotation = transformComponent.m_Rotation;
			auto& scale = transformComponent.m_Scale;
			//ImGui::DragFloat3("Translation", &translation[0], 0.1f, -9999.0f, 9999.0f);
			//ImGui::DragFloat3("Rotation", &rotation[0], 0.1f, -9999.0f, 9999.0f);
			//ImGui::DragFloat3("Scale", &scale[0], 0.1f, -9999.0f, 9999.0f);

			DrawVec3("Translation", translation, glm::vec3(0.0f));
			glm::vec3 angleRotation = glm::degrees(rotation);
			DrawVec3("Rotation", angleRotation, glm::vec3(0.0f));
			rotation = glm::radians(angleRotation);
			DrawVec3("Scale", scale, glm::vec3(1.0f));

			ImGui::TreePop();
		}
	}

	//mesh component
	if (m_SelectedEntity.HasComponent<MeshComponent>())
	{
		if (ImGui::TreeNode("MeshComponent"))
		{
			auto& meshComponent = m_SelectedEntity.GetComponent<MeshComponent>();
			char buffer[256];
			memset(buffer, 0, sizeof(buffer));
			memcpy_s(buffer, sizeof(buffer), meshComponent.m_MeshFilePath.c_str(), sizeof(buffer));
			if (ImGui::InputText("MeshFilePath", buffer, sizeof(buffer)))
			{
				meshComponent.LoadMesh(buffer);
			}

			ImGui::TreePop();
		}
	}

	//material component
	if (m_SelectedEntity.HasComponent<MaterialComponent>())
	{
		if (ImGui::TreeNode("MaterialComponent"))
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

			ImGui::TreePop();
		}
	}

	//camera component
	if (m_SelectedEntity.HasComponent<CameraComponent>())
	{
		auto& cameraComponent = m_SelectedEntity.GetComponent<CameraComponent>();
		ImGui::DragFloat("MoveSpeed", &cameraComponent.m_MoveSpeed, 1.0f, 0.0f, 9999.0f);
		
		if (ImGui::DragFloat("FovY", &cameraComponent.fovy, 1.0f, -9999.0f, 9999.0f) ||
			ImGui::DragFloat("Aspect", &cameraComponent.aspect, 1.0f, -9999.0f, 9999.0f) ||
			ImGui::DragFloat("NearZ", &cameraComponent.nearz, 1.0f, -9999.0f, 9999.0f) ||
			ImGui::DragFloat("FarZ", &cameraComponent.farz, 1.0f, -9999.0f, 9999.0f))
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
	}

	////test
	//if (m_SelectedEntity.GetComponent<TagComponent>().m_Tag == "plane Entity")
	//{
	//	static bool flag= true;
	//	ImGui::Checkbox("test loadmesh", &flag);

	//	if (!flag)
	//	{
	//		m_SelectedEntity.GetComponent<MeshComponent>().LoadMesh("assets/model/plane_mesh.bin");
	//	}
	//	else
	//		m_SelectedEntity.GetComponent<MeshComponent>().LoadMesh("assets/model/cube_mesh.bin");
	//}
}


END_ENTERNITY

