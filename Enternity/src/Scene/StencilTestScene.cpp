#include "StencilTestScene.h"
#include "Core/Reflection/Reflection.h"
#include "Common/Camera3D.h"
#include "Common/CameraController.h"
#include "Common/Light.h"
#include "Common/CubeObject.h"
#include "Common/ModelObject.h"
#include "Common/ModelObject2.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"
#include <glad/glad.h>

namespace Enternity
{
	REGISTER_CLASS(IScene, "StencilTestScene", StencilTestScene);

	void StencilTestScene::Initialize()
	{
		if (m_bIsInit)
			return;

		m_pCamera3D = new Camera3D;
		m_pCamera3D->m_transform.m_Translation = glm::vec3(0.620f, 2.403f, 10.135f);
		m_pCamera3D->m_transform.m_Rotation = glm::vec3(-0.131f, 0.055f, 0.000);
		m_pCameraController = new CameraController(m_pCamera3D);
		m_pLight = new Light(m_pCamera3D);


	
		m_pPlaneObject = new CubeObject(m_pCamera3D, m_pLight);
		m_pPlaneObject->m_transform.m_Scale = { 10.0f, 0.1f, 10.0f };

		m_pCube = new CubeObject(m_pCamera3D, m_pLight);
		m_pCube->m_transform.m_Translation = { -2.0f, 1.0f, 0.0f };

		m_pModelObject = new ModelObject(m_pCamera3D, m_pLight);
		m_pModelObject->Load("assets/models/planet/planet.obj");
		m_pModelObject->m_transform.m_Translation.y = 1;		
		

		m_pModelObject2 = new ModelObject2(m_pCamera3D, m_pLight);
		m_pModelObject2->Load("assets/models/planet/planet.obj");
		m_pModelObject2->m_transform.m_Translation.y = 1;
		m_pModelObject2->m_transform.m_Scale = {0.32f, 0.32f, 0.32f };

		glEnable(GL_STENCIL_TEST);

		m_bIsInit = true;
	}

	void StencilTestScene::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pCamera3D);
		SAFE_DELETE_SET_NULL(m_pCameraController);
		SAFE_DELETE_SET_NULL(m_pLight);

		SAFE_DELETE_SET_NULL(m_pPlaneObject);
		SAFE_DELETE_SET_NULL(m_pModelObject);
		SAFE_DELETE_SET_NULL(m_pModelObject2);
		SAFE_DELETE_SET_NULL(m_pCube);

	}

	void StencilTestScene::Tick(float deltaTime)
	{
		m_pPlaneObject->Draw();
		

		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		m_pModelObject->Draw();

		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		m_pModelObject2->Draw();


		//m_pLight->Draw();
	}

	void StencilTestScene::RecompileShader()
	{
		m_pPlaneObject->RecompileShader();
	}

	void StencilTestScene::RenderGUI()
	{
		ImGui::Begin("StencilTestScene");

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

		m_pPlaneObject->RenderGUI();
		m_pModelObject->RenderGUI();
		m_pModelObject2->RenderGUI();

		ImGui::End();
	}

	void StencilTestScene::OnResize(int width, int height)
	{
		m_pCamera3D->aspect = static_cast<float>(width) / height;
	}
}