#include "UiRenderSystem.h"
#include "Core/Log/Log.h"
#include "Platform/Window/OpenglWindow.h"
#include "Function/Scene/SceneManager.h"
#include "Function/Scene/ECS/Component/TransformComponent.h"

#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

namespace Enternity
{
	void UiRenderSystem::initialize(OpenglWindow* window)
	{
		ENTERNITY_ASSERT(window != nullptr);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO &io = ImGui::GetIO();
		(void)io;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Bold.ttf", 20);
		io.FontDefault = io.Fonts->AddFontFromFileTTF("assets/fonts/opensans/OpenSans-Regular.ttf", 20);

		setDarkThemeColors();

		ImGui_ImplGlfw_InitForOpenGL(window->getContext(), true);
		ImGui_ImplOpenGL3_Init("#version 440");

		LOG_INFO("UiRenderSystem initialization");
	}

	void UiRenderSystem::uninitialize()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		LOG_INFO("UiRenderSystem uninitialization");
	}

	void UiRenderSystem::tick()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::ShowMetricsWindow();

		ImGui::Begin("Debug");
		Scene* scene = SceneManager::GetInstance().getScene();
		auto iter = scene->m_entities.begin();
		auto& comp = iter->second.getComponent<TransformComponent>();
		
		ImGui::DragFloat("transX", &comp.m_position.x, 1.0f);
		ImGui::DragFloat("transY", &comp.m_position.y, 1.0f);
		ImGui::DragFloat("transZ", &comp.m_position.z, 1.0f);

		
		ImGui::DragFloat("rotX", &comp.m_rotation.x, 1.0f);
		ImGui::DragFloat("rotY", &comp.m_rotation.y, 1.0f);
		ImGui::DragFloat("rotZ", &comp.m_rotation.z, 1.0f);

		ImGui::DragFloat("scaleX", &comp.m_scale.x, 1.0f);
		ImGui::DragFloat("scaleY", &comp.m_scale.y, 1.0f);
		ImGui::DragFloat("scaleZ", &comp.m_scale.z, 1.0f);

		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void UiRenderSystem::setDarkThemeColors()
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
}