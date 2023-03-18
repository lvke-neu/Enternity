#include "PhongScene.h"
#include "Core/Reflection/Reflection.h"
#include "Common/Camera3D.h"
#include "Common/CameraController.h"
#include "Common/Light.h"
#include "Common/CubeObject.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"


namespace Enternity
{
	REGISTER_CLASS(IScene, "PhongScene", PhongScene);

	void PhongScene::Initialize()
	{
		if (m_bIsInit)
			return;

		m_pCamera3D = new Camera3D;
		m_pCamera3D->m_transform.m_Translation = glm::vec3(0.0f, 0.0f, 5.0f);
		m_pCameraController = new CameraController(m_pCamera3D);
		m_pLight = new Light(m_pCamera3D);


		glm::vec3 cubePositions[] = {
				glm::vec3(0.0f,  0.0f,  0.0f),
				glm::vec3(2.0f,  5.0f, -15.0f),
				glm::vec3(-1.5f, -2.2f, -2.5f),
				glm::vec3(-3.8f, -2.0f, -12.3f),
				glm::vec3(2.4f, -0.4f, -3.5f),
				glm::vec3(-1.7f,  3.0f, -7.5f),
				glm::vec3(1.3f, -2.0f, -2.5f),
				glm::vec3(1.5f,  2.0f, -2.5f),
				glm::vec3(1.5f,  0.2f, -1.5f),
				glm::vec3(-1.3f,  1.0f, -1.5f)
		};
		for (int i = 0; i < 10; i++)
		{
			m_pCubeObjects.emplace_back(new CubeObject(m_pCamera3D, m_pLight));
			m_pCubeObjects[i]->m_transform.m_Translation = cubePositions[i];
			m_pCubeObjects[i]->m_transform.m_Rotation = cubePositions[i];
		}

		m_bIsInit = true;
	}

	void PhongScene::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pCamera3D);
		SAFE_DELETE_SET_NULL(m_pCameraController);
		SAFE_DELETE_SET_NULL(m_pLight);
		for (auto& cubeObject : m_pCubeObjects)
		{
			SAFE_DELETE_SET_NULL(cubeObject);
		}
	}

	void PhongScene::Tick(float deltaTime)
	{
		for (auto& cubeObject : m_pCubeObjects)
		{
			cubeObject->Draw();
		}
		m_pLight->Draw();
	}

	void PhongScene::RecompileShader()
	{
		for (auto& cubeObject : m_pCubeObjects)
		{
			cubeObject->RecompileShader();
		}
	}

	void PhongScene::RenderGUI()
	{
		ImGui::Begin("PhongScene");

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

		//m_pCubeObject->RenderGUI();

		ImGui::End();
	}

	void PhongScene::OnResize(int width, int height)
	{
		m_pCamera3D->aspect = static_cast<float>(width) / height;
	}
}