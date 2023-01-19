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

	ImGui::End();

}

END_ENTERNITY


