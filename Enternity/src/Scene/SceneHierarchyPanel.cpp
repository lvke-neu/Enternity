#include "SceneHierarchyPanel.h"
#include "Imgui/ImguiManager.h"
#include "Log/Log.h"
#include "ECS/Component/Component.h"

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
	auto& tagComponent = m_SelectedEntity.GetComponent<TagComponent>();
	char buffer[256];
	memset(buffer, 0, sizeof(buffer));
	memcpy_s(buffer, sizeof(buffer), tagComponent.m_Tag.c_str(), sizeof(buffer));
	if (ImGui::InputText("Name", buffer, sizeof(buffer)))
	{
		tagComponent.m_Tag = buffer;
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
			ImGui::DragFloat3("Translation", &translation[0], 0.1f, -9999.0f, 9999.0f);
			ImGui::DragFloat3("Rotation", &rotation[0], 0.1f, -9999.0f, 9999.0f);
			ImGui::DragFloat3("Scale", &scale[0], 0.1f, -9999.0f, 9999.0f);

			ImGui::TreePop();
		}
	}

	//mesh component
	if (m_SelectedEntity.HasComponent<MeshComponent>())
	{
		if (ImGui::TreeNode("MeshComponent"))
		{
			ImGui::Text("TestMeshComponent");

			ImGui::TreePop();
		}
	}

	//camera component
	if (m_SelectedEntity.HasComponent<CameraComponent>())
	{
		auto& cameraComponent = m_SelectedEntity.GetComponent<CameraComponent>();
		ImGui::DragFloat("MoveSpeed", &cameraComponent.m_MoveSpeed, 1.0f, 0.0f, 9999.0f);

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

