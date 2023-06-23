#pragma warning(disable:4312) 

#include "ViewPortPanel.h"
#include "Engine/Engine.h"
#include "Engine/RenderView.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/FrameBuffer/FrameBuffer.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"


namespace Enternity
{
	void ViewPortPanel::draw()
	{
		ImGui::Begin("Viewport");
		
		onViewPortResize();

		auto id = Engine::GetInstance().getGraphicsSystem()->getFrameBuffer()->getTextureId();
		ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

		ImGui::End();
	}

	void ViewPortPanel::onViewPortResize()
	{
		auto viewport = ImGui::GetContentRegionAvail();
		if (m_width != viewport.x || m_height != viewport.y)
		{
			m_width = (unsigned int)viewport.x;
			m_height = (unsigned int)viewport.y;
			Engine::GetInstance().getRenderView()->Resize(m_width, m_height);
		}
	}

}