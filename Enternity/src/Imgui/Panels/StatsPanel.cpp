#pragma warning(disable:4312) 

#include "StatsPanel.h"
#include "Scene/SceneManager.h"
#include "../ImguiManager.h"

BEGIN_ENTERNITY

StatsPanel::StatsPanel() : IPanel()
{

}

StatsPanel::~StatsPanel()
{

}

void StatsPanel::ImguiDraw()
{
	ImGui::Begin("Stats");
	ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


	std::string currentCameraTag = "";
	Entity currentCamaeraEntity = SceneManager::GetInstance().m_SceneState == SceneState::Editor ? SceneManager::GetInstance().m_EditorCameraEntity : SceneManager::GetInstance().m_PlayerCameraEntity;
	if (currentCamaeraEntity.IsValidEntity())
		currentCameraTag = currentCamaeraEntity.GetComponent<TagComponent>().m_Tag;
	ImGui::Text("Current Camera: %s", currentCameraTag.c_str());



	int hoverEntityId = ImguiManager::GetInstance().GetViewportPanel()->GetHoverEntityId();
	//LOG_INFO(std::to_string(hoverEntityId));
	std::string tag;
	if (hoverEntityId > -1)
	{
		Entity tmpEntity(&SceneManager::GetInstance().m_Registry, (entt::entity)hoverEntityId);
		if (tmpEntity.IsValidEntityEx())
		{
			tag = tmpEntity.GetComponent<TagComponent>().m_Tag;
		}
		else
		{
			tag = "";
			hoverEntityId = -1;
		}
	}
	else
	{
		tag = "";
		hoverEntityId = -1;
	}
	ImGui::Text("Hoverd Entity: %s, id = %d", tag.c_str(), hoverEntityId);

	//ImGui::ShowMetricsWindow();

	ImGui::End();
}

END_ENTERNITY


