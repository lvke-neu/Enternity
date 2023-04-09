#include "SkyboxScene.h"
#include "Core/Reflection/Reflection.h"
#include "Common/Camera3D.h"
#include "Common/CameraController.h"
#include "Common/Light.h"
#include "Common/CubeObject.h"
#include "Common/ModelObject.h"
#include "Common/ModelObject2.h"
#include "Common/QuadObject.h"
#include "Common/SkyboxObject.h"
#include "RHI/Texture.h"
#include "RHI/FrameBuffer.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"
#include <glad/glad.h>

#pragma warning(disable:4312)

namespace Enternity
{
	REGISTER_CLASS(IScene, "SkyboxScene", SkyboxScene);

	void SkyboxScene::Initialize()
	{
		if (m_bIsInit)
			return;

		m_pCamera3D = new Camera3D;
		m_pCamera3D->m_transform.m_Translation = glm::vec3(0.620f, 2.403f, 10.135f);
		m_pCamera3D->m_transform.m_Rotation = glm::vec3(-0.131f, 0.055f, 0.000);
		m_pCameraController = new CameraController(m_pCamera3D);
		m_pLight = new Light(m_pCamera3D);

		m_pCube = new CubeObject(m_pCamera3D, m_pLight);
		m_pCube->m_transform.m_Translation = { -2.0f, 1.0f, 0.0f };

		m_pSkyboxObject = new SkyboxObject(m_pCamera3D);

		m_bIsInit = true;
	}

	void SkyboxScene::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pCamera3D);
		SAFE_DELETE_SET_NULL(m_pCameraController);
		SAFE_DELETE_SET_NULL(m_pLight);
		SAFE_DELETE_SET_NULL(m_pCube);
		SAFE_DELETE_SET_NULL(m_pSkyboxObject);
	}

	void SkyboxScene::Tick(float deltaTime)
	{
		m_pCube->Draw();
		m_pSkyboxObject->Draw();
	}

	void SkyboxScene::RecompileShader()
	{
		
	}

	void SkyboxScene::RenderGUI()
	{
	

	
	}

	void SkyboxScene::OnResize(int width, int height)
	{
		m_pCamera3D->aspect = static_cast<float>(width) / height;
	}
}