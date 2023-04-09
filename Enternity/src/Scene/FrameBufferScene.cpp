#include "FrameBufferScene.h"
#include "Core/Reflection/Reflection.h"
#include "Common/Camera3D.h"
#include "Common/CameraController.h"
#include "Common/Light.h"
#include "Common/CubeObject.h"
#include "Common/ModelObject.h"
#include "Common/ModelObject2.h"
#include "RHI/Texture.h"
#include "RHI/FrameBuffer.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"
#include <glad/glad.h>

#pragma warning(disable:4312)

namespace Enternity
{
	REGISTER_CLASS(IScene, "FrameBufferScene", FrameBufferScene);

	void FrameBufferScene::Initialize()
	{
		if (m_bIsInit)
			return;

		m_pFrameBuffer = new FrameBuffer;


		m_pCamera3D = new Camera3D;
		m_pCamera3D->m_transform.m_Translation = glm::vec3(0.620f, 2.403f, 10.135f);
		m_pCamera3D->m_transform.m_Rotation = glm::vec3(-0.131f, 0.055f, 0.000);
		m_pCameraController = new CameraController(m_pCamera3D);
		m_pLight = new Light(m_pCamera3D);

		m_pCube = new CubeObject(m_pCamera3D, m_pLight);
		m_pCube->m_transform.m_Translation = { -2.0f, 1.0f, 0.0f };

		m_pModelObject = new ModelObject(m_pCamera3D, m_pLight);
		m_pModelObject->Load("assets/models/planet/planet.obj");
		m_pModelObject->m_transform.m_Translation.y = 1;


		m_pModelObject2 = new ModelObject2(m_pCamera3D, m_pLight);
		m_pModelObject2->Load("assets/models/planet/planet.obj");
		m_pModelObject2->m_transform.m_Translation.y = 1;
		m_pModelObject2->m_transform.m_Scale = { 0.32f, 0.32f, 0.32f };

		//glEnable(GL_STENCIL_TEST);

		m_bIsInit = true;
	}

	void FrameBufferScene::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pCamera3D);
		SAFE_DELETE_SET_NULL(m_pCameraController);
		SAFE_DELETE_SET_NULL(m_pLight);
		SAFE_DELETE_SET_NULL(m_pCube);
		SAFE_DELETE_SET_NULL(m_pModelObject);
		SAFE_DELETE_SET_NULL(m_pModelObject2);

	}

	void FrameBufferScene::Tick(float deltaTime)
	{
		m_pFrameBuffer->bind();
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		//m_pModelObject->Draw();

		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		//m_pModelObject2->Draw();

		m_pCube->Draw();

		m_pFrameBuffer->unbind();
	}

	void FrameBufferScene::RecompileShader()
	{
		m_pCube->RecompileShader();
	}

	void FrameBufferScene::RenderGUI()
	{
		// If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
	// In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
	// In this specific demo, we are not using DockSpaceOverViewport() because:
	// - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
	// - we allow the host window to have padding (when opt_padding == true)
	// - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
	// TL;DR; this demo is more complicated than what you would normally use.
	// If we removed all the options we are showcasing, this demo would become:
	//     void ShowExampleAppDockSpace()
	//     {
	//         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	//     }

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		static bool p_open = true;
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
	

		ImGui::Begin("FrameBufferSceneViewport");

		//viewport resize
		static int width = -1;
		static int height = -1;
		auto viewport = ImGui::GetContentRegionAvail();
		if (width != viewport.x || height != viewport.y)
		{
			width = (uint32_t)viewport.x;
			height = (uint32_t)viewport.y;
			glViewport(0, 0, width, height);
			m_pCamera3D->aspect = static_cast<float>(width) / height;
			m_pFrameBuffer->resize(width, height);
		}
		//***********************


		auto id = m_pFrameBuffer->getTextureId();
		ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

		ImGui::End();


		ImGui::Begin("FrameBufferSceneProperty");
		m_pCube->RenderGUI();
		ImGui::End();
		ImGui::End();

	
	}

	void FrameBufferScene::OnResize(int width, int height)
	{
		m_pCamera3D->aspect = static_cast<float>(width) / height;
	}
}