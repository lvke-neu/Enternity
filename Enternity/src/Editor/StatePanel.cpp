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

namespace Enternity
{
	void StatePanel::treeNode(Node* node)
	{
		if (ImGui::TreeNode(node->get_name().c_str()))
		{
			for (auto child : node->get_childs())
			{
				treeNode(child);
			}
			ImGui::TreePop();
		}
	}


	StatePanel::StatePanel()
	{
		m_rootNode = new Node;
		m_rootNode->set_name("RootNode");

		for (int i = 0; i < 5; i++)
		{
			Node* node = new Node;
			node->set_name(std::to_string(i).c_str());
			node->addToParent(m_rootNode);

			for (int j = 0; j < 5; j++)
			{
				Node* node2 = new Node;
				node2->set_name(std::to_string(i) + "_" + std::to_string(j));
				node2->addToParent(node);
			}
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

		//Node* rootNode = Engine::GetInstance().getSceneManager()->getCurrentScene()->getRootNode();
		treeNode(m_rootNode);

		ImGui::End();
	}
}