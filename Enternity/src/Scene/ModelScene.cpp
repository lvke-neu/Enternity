#include "ModelScene.h"
#include "Core/Reflection/Reflection.h"
#include "Common/Camera3D.h"
#include "Common/CameraController.h"
#include "Common/Light.h"
#include "Common/ModelObject.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"

namespace Enternity
{
	REGISTER_CLASS(IScene, "ModelScene", ModelScene);

	void ModelScene::Initialize()
	{
		if (m_bIsInit)
			return;

		m_pCamera3D = new Camera3D;
		m_pCamera3D->m_transform = { {-1.742f, 4.0f, 5.409f},{-0.551f, -0.287f, 0.0f},{1.0f, 1.0f, 1.0f} };


		m_pCameraController = new CameraController(m_pCamera3D);
		m_pLight = new Light(m_pCamera3D);
		m_pLight->m_transform.m_Translation = { -1.700f, 2.100, 1.100 };

		m_pModelObject = new ModelObject(m_pCamera3D, m_pLight);
		m_pModelObject->Load("assets/models/nanosuit/nanosuit.obj");

		m_bIsInit = true;
	}

	void ModelScene::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pCamera3D);
		SAFE_DELETE_SET_NULL(m_pCameraController);
		SAFE_DELETE_SET_NULL(m_pLight);
		SAFE_DELETE_SET_NULL(m_pModelObject);
	}

	void ModelScene::Tick(float deltaTime)
	{
		m_pModelObject->Draw();
		m_pLight->Draw();
	}

	void ModelScene::RecompileShader()
	{

	}

	void ModelScene::RenderGUI()
	{
		ImGui::Begin("ModelScene");

		ImGui::DragFloat3("camtransaltion", &m_pCamera3D->m_transform.m_Translation[0], 0.1f);
		ImGui::DragFloat3("camrotation", &m_pCamera3D->m_transform.m_Rotation[0], 1);
		ImGui::Separator();
		ImGui::DragFloat3("lighttransaltion", &m_pLight->m_transform.m_Translation[0], 0.1f);
		ImGui::DragFloat3("lightscale", &m_pLight->m_transform.m_Scale[0], 0.1f);
		if (ImGui::Button("Reset Camera"))
		{
			m_pCamera3D->m_transform.m_Translation = { 0.0f };
			m_pCamera3D->m_transform.m_Rotation = { 0.0f };
		}
		ImGui::Separator();
		ImGui::Separator();
		ImGui::Separator();

		m_pModelObject->RenderGUI();

		ImGui::End();
	}

	void ModelScene::OnResize(int width, int height)
	{
		m_pCamera3D->aspect = static_cast<float>(width) / height;
	}
}