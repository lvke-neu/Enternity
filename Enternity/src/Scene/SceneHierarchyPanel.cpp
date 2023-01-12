#include "SceneHierarchyPanel.h"
#include "Imgui/ImguiManager.h"
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
			ImGui::Text(entity.GetComponent<TagComponent>().m_Tag.c_str());
		}
	);


	ImGui::End();

}


END_ENTERNITY

