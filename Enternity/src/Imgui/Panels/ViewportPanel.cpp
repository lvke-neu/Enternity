#pragma warning(disable:4312) 

#include "ViewportPanel.h"
#include "Engine/Engine.h"
#include "Event/InputEventManager.h"
#include "Scene/SceneSerializer.h"
#include "Scene/SceneManager.h"
#include "../ImguiManager.h"
#include "Math/Math.h"


BEGIN_ENTERNITY

ViewportPanel::ViewportPanel() : IPanel()
{

}

Enternity::ViewportPanel::~ViewportPanel()
{

}

void Enternity::ViewportPanel::ImguiDraw()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

	ImGui::Begin("viewport");


	auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
	auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
	auto viewportOffset = ImGui::GetWindowPos();
	m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
	m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

	InputEventManager::GetInstance().SetViewportFocused(ImGui::IsWindowHovered());

	auto viewport = ImGui::GetContentRegionAvail();
	if (m_width != viewport.x || m_height != viewport.y)
	{
		m_width = (uint32_t)viewport.x;
		m_height = (uint32_t)viewport.y;
		Engine::GetInstance().Resize(m_width, m_height);
	}


	auto id = Engine::GetInstance().GetFrameBufferEx()->GetTextureRendererId(0);
	ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

	//drag
	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
		{
			LOG_INFO((char*)payload->Data);
			std::string path((char*)payload->Data);
			path = path.substr(0, payload->DataSize);

			ImguiManager::GetInstance().GetSceneHierarchyPanel()->SetSelectedEntityNull();
			SceneManager::GetInstance().Clear();
			SceneSerializer::Deserialize(path);
		}
		ImGui::EndDragDropTarget();
	}

	//Gizmos
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_4))
		m_GizmoType = -1;
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_1))
		m_GizmoType = 0;
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_2))
		m_GizmoType = 1;
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_3))
		m_GizmoType = 2;

	Entity selectedEntity = ImguiManager::GetInstance().GetSceneHierarchyPanel()->GetSelectedEntity();
	if (selectedEntity.IsValidEntity() && selectedEntity.HasComponent<TransformComponent>())
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		auto mainCameraEntity = SceneManager::GetInstance().GetMainCameraEntity();
		const auto& viewMatrix = mainCameraEntity.GetComponent<TransformComponent>().GetInverseWorldMatrix();
		const auto& projMatrix = mainCameraEntity.GetComponent<CameraComponent>().m_ProjectMatrix;

		auto modelMatrix = selectedEntity.GetComponent<TransformComponent>().GetWorldMatrix();

		if(SceneManager::GetInstance().m_SceneState == SceneState::Editor)
			ImGuizmo::Manipulate(&viewMatrix[0][0], &projMatrix[0][0], (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::MODE::LOCAL, &modelMatrix[0][0]);

		if (ImGuizmo::IsUsing())
		{
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			Math::DecomposeTransform(modelMatrix, tc.m_Translation, tc.m_Rotation, tc.m_Scale);
		}
	}

	ImGui::End();
	ImGui::PopStyleVar();



	//mouse pick
	Engine::GetInstance().GetFrameBufferEx()->Bind();
	auto[mx, my] = ImGui::GetMousePos();

	mx -= m_ViewportBounds[0].x;
	my -= m_ViewportBounds[0].y;

	int mouseX = (int)mx;
	int mouseY = (int)my;

	auto viewportSizeX = m_ViewportBounds[1].x - m_ViewportBounds[0].x;
	auto viewportSizeY = m_ViewportBounds[1].y - m_ViewportBounds[0].y;
	mouseY = int(viewportSizeY - my);
	if (mouseX >= 0 && mouseY >= 0 && mouseX <= viewportSizeX && mouseY <= viewportSizeY)
	{
		m_MousePickPixelEntityId = Engine::GetInstance().GetFrameBufferEx()->ReadPixel(1, mouseX, mouseY);
		if (InputEventManager::GetInstance().IsMousePress(MouseButton::GLFW_MOUSE_BUTTON_LEFT)
			&& !ImGuizmo::IsUsing()
			&& !SceneManager::GetInstance().IsWireFrame())
		{
			//LOG_INFO("Hit:" + std::to_string(Engine::GetInstance().GetFrameBufferEx()->ReadPixel(1, mouseX, mouseY)));

			ImguiManager::GetInstance().GetSceneHierarchyPanel()->SetSelectedEntity(m_MousePickPixelEntityId);
			
		}
	}
	Engine::GetInstance().GetFrameBufferEx()->UnBind();
}

END_ENTERNITY


