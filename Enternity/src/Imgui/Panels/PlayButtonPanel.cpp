#pragma warning(disable:4312) 

#include "PlayButtonPanel.h"
#include "Scene/SceneManager.h"
#include "../ImguiManager.h"

BEGIN_ENTERNITY

PlayButtonPanel::PlayButtonPanel() : IPanel()
{
	m_EditorTexture = new Texture("Resource/PlayButton.png");
	m_PlayerTexture = new Texture("Resource/StopButton.png");
}

PlayButtonPanel::~PlayButtonPanel()
{
	SAFE_DELETE_SET_NULL(m_EditorTexture);
	SAFE_DELETE_SET_NULL(m_PlayerTexture);
}

void PlayButtonPanel::ImguiDraw()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
	ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
	auto& colors = ImGui::GetStyle().Colors;
	const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
	const auto& buttonActive = colors[ImGuiCol_ButtonActive];
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

	ImGui::Begin("##PlayButton", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

	auto size = ImGui::GetWindowHeight() - 4;
	ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
	auto curretnTexture = SceneManager::GetInstance().m_SceneState == SceneState::Editor ? m_EditorTexture : m_PlayerTexture;

	if (ImGui::ImageButton((ImTextureID)curretnTexture->GetRendererId(), { size, size }, { 0, 0 }, { 1,1 }, 0))
	{
		if (SceneManager::GetInstance().m_SceneState == SceneState::Editor)
		{
			SceneManager::GetInstance().OnPlay();
		}
		else
		{
			SceneManager::GetInstance().OnEditor();

			////reload scene(temporary)
			//ImguiManager::GetInstance().GetViewportPanel()->LoadScene();
		}
	}
	
	ImGui::PopStyleVar(2);
	ImGui::PopStyleColor(3);

	ImGui::End();
}

END_ENTERNITY

