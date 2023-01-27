#pragma warning(disable:4312) 

#include "ViewportPanel2.h"
#include "Scene/ShadowMap/ShadowMapManager.h"

BEGIN_ENTERNITY

ViewportPanel2::ViewportPanel2() : IPanel()
{

}

ViewportPanel2::~ViewportPanel2()
{

}

void ViewportPanel2::ImguiDraw()
{
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

	ImGui::Begin("viewport2");

	auto id = ShadowMapManager::GetInstance().GetFrameBufferShadowMap()->GetTextureRendererId();
	ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

	ImGui::End();
	ImGui::PopStyleVar();
}

END_ENTERNITY


