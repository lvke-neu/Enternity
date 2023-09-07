#pragma warning(disable:4312) 

#include "StatePanel.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/FrameBuffer/FrameBuffer.h"
#include "Pick/PickSystem.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneGraph/Node3D.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include <rttr/type.h>

namespace Enternity
{
	void StatePanel::treeNode(Node* node)
	{
		if (ImGui::TreeNode(node->get_name().c_str()))
		{
			rttr::type type = rttr::type::get_by_name("Node");

			for (auto& prop : type.get_properties())
			{
				
				ImGui::Separator();

				ImGui::Text("name:%s, type:%s", prop.get_name().data(), prop.get_type().get_name().data());
				for (auto& pp : prop.get_type().get_properties())
				{
					ImGui::Text("name2:%s, type2:%s", pp.get_name().data(), pp.get_type().get_name().data());
				}
				ImGui::Separator();
			}
			

			//for (auto child : node->getChilds())
			//{
			//	treeNode(child);
			//}
			ImGui::TreePop();
		}
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

		ImGui::Begin("SceneGraph");

		Node* rootNode = Engine::GetInstance().getSceneManager()->getCurrentScene()->getRootNode();
		treeNode(rootNode);

		ImGui::End();
	}
}