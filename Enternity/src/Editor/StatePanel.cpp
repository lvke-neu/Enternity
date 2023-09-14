#pragma warning(disable:4312) 

#include "StatePanel.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/FrameBuffer/FrameBuffer.h"
#include "Pick/PickSystem.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

namespace Enternity
{
	StatePanel::StatePanel()
	{

	}

	void StatePanel::draw()
	{
		ImGui::Begin("State");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::Text("TriangleCount:%d", Engine::GetInstance().getGraphicsSystem()->getTriangleCount());
		//ImGui::Text("Picked Entity ID:%d", Engine::GetInstance().getPickSystem()->getPickEntityId());
		ImGui::End();


		//ImGui::Begin("Depth");

		//auto id = Engine::GetInstance().getGraphicsSystem()->getColorFrameBuffer()->getTextureId(1);
		////ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

		//ImGui::End();

		ImGui::Begin("ShadowMap");

		auto id = Engine::GetInstance().getGraphicsSystem()->getShadowMapFrameBuffer()->getTextureId();
		//ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

		ImGui::End();
	}
}