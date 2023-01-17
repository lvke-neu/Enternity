#pragma warning(disable:4312) 

#include "ImguiManager.h"
#include "ImguiImpl/ImGuizmo.h"
#include "Engine/Engine.h"
#include "Event/InputEventManager.h"
#include "Event/ImguiDrawEventManager.h"
#include "Scene/SceneManager.h"
#include "Scene/SceneSerializer.h"
#include "Dialog/FileDialog.h"
#include "Math/Math.h"

BEGIN_ENTERNITY

void ImguiManager::Initialize(GLFWwindow* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 20);
	io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 20);

	SetDarkThemeColors();

	ImGui_ImplGlfw_InitForOpenGL(context, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImguiManager::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	static bool b = true;


	ShowDockSpace(&b);
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::Release()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiManager::ShowDockSpace(bool* p_open)
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
	ImGui::Begin("DockSpace Demo", p_open, window_flags);
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

	if (ImGui::BeginMenuBar())
	{	
		if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_LEFT_CONTROL) && InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_N))
			SceneManager::GetInstance().Clear();

		if(InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_LEFT_CONTROL) && InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_O))
			SceneSerializer::Deserialize(FileDialog::OpenFile(".scene"));

		if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_LEFT_CONTROL) && InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_S))
			SceneSerializer::Serialize(FileDialog::SaveFile(".scene"));

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New", "CTRL+N"))
			{
				SceneManager::GetInstance().Clear();
			}
			if (ImGui::MenuItem("Open...", "CTRL+O"))
			{
				SceneSerializer::Deserialize(FileDialog::OpenFile(".scene"));
			}
			if (ImGui::MenuItem("Save...", "CTRL+S"))
			{
				SceneSerializer::Serialize(FileDialog::SaveFile(".scene"));
			}

			if (ImGui::MenuItem("Close"))
				Engine::GetInstance().ShutDown();

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	//ImGui::ShowDemoWindow(p_open);
	//ImGui::ShowMetricsWindow(p_open);

	//test image
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });
	ImGui::Begin("viewport");

	InputEventManager::GetInstance().SetViewportFocused(ImGui::IsWindowHovered());

	auto viewport = ImGui::GetContentRegionAvail();
	if (m_width != viewport.x || m_height != viewport.y)
	{
		m_width = (uint32_t)viewport.x;
		m_height = (uint32_t)viewport.y;
		Engine::GetInstance().Resize(m_width, m_height);
	}
	
	auto id = Engine::GetInstance().GetFrameBufferEx()->GetTextureRendererId(2);
	ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
		{
			LOG_INFO((char*)payload->Data);
			std::string path((char*)payload->Data);
			path = path.substr(0, payload->DataSize);
			SceneSerializer::Deserialize(path);
		}
		ImGui::EndDragDropTarget();
	}


	//Gizmos
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_4))
		m_GizmoType = -1;
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_1))
		m_GizmoType = 0;
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_2))
		m_GizmoType = 1;
	if (InputEventManager::GetInstance().IsKeyPress(Keyboard::GLFW_KEY_3))
		m_GizmoType = 2;

	Entity selectedEntity = SceneManager::GetInstance().GetSceneHierarchyPanel()->GetSelectedEntity();
	if (selectedEntity.IsValidEntity() && selectedEntity.HasComponent<TransformComponent>())
	{
		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		auto mainCameraEntity = SceneManager::GetInstance().GetMainCameraEntity();
		const auto& viewMatrix = mainCameraEntity.GetComponent<TransformComponent>().GetInverseWorldMatrix();
		const auto& projMatrix = mainCameraEntity.GetComponent<CameraComponent>().m_ProjectMatrix;

		auto modelMatrix = selectedEntity.GetComponent<TransformComponent>().GetWorldMatrix();
			
		ImGuizmo::Manipulate(&viewMatrix[0][0], &projMatrix[0][0], (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::MODE::LOCAL, &modelMatrix[0][0]);

		if (ImGuizmo::IsUsing())
		{
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			Math::DecomposeTransform(modelMatrix, tc.m_Translation, tc.m_Rotation, tc.m_Scale);
		}
	}

	ImGui::End();
	ImGui::PopStyleVar();

	//imgui draw
	ImguiDrawEventManager::GetInstance().NotifyImguiDraw();


	ImGui::End();
}

void ImguiManager::SetDarkThemeColors()
{
	auto& colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

	// Headers
	colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Buttons
	colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Frame BG
	colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
	colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
	colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

	// Tabs
	colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
	colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
	colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

	// Title
	colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
}

END_ENTERNITY