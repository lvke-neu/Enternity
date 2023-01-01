#include "ImguiManager.h"
#include "Imgui/ImguiImpl/imgui.h"
#include "Imgui/ImguiImpl/imgui_impl_glfw.h"
#include "Imgui/ImguiImpl/imgui_impl_opengl3.h"

BEGIN_ENTERNITY

void ImguiManager::Initialize(GLFWwindow* context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui_ImplGlfw_InitForOpenGL(context, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void ImguiManager::Draw()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	static bool b = true;
	ImGui::ShowDemoWindow(&b);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiManager::Release()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

END_ENTERNITY