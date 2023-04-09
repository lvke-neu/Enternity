#include "FrameBufferScene2.h"
#include "Core/Reflection/Reflection.h"
#include "Common/Camera3D.h"
#include "Common/CameraController.h"
#include "Common/Light.h"
#include "Common/CubeObject.h"
#include "Common/ModelObject.h"
#include "Common/ModelObject2.h"
#include "Common/QuadObject.h"
#include "RHI/Texture.h"
#include "RHI/FrameBuffer.h"
#include "Utility/Utility.h"
#include "GUI/GUIRender.h"
#include <glad/glad.h>

#pragma warning(disable:4312)

namespace Enternity
{
	REGISTER_CLASS(IScene, "FrameBufferScene2", FrameBufferScene2);

	void FrameBufferScene2::Initialize()
	{
		if (m_bIsInit)
			return;

		m_pFrameBuffer = new FrameBuffer;
		m_pFrameBuffer->init(1200, 800);

		m_pCamera3D = new Camera3D;
		m_pCamera3D->m_transform.m_Translation = glm::vec3(0.620f, 2.403f, 10.135f);
		m_pCamera3D->m_transform.m_Rotation = glm::vec3(-0.131f, 0.055f, 0.000);
		m_pCameraController = new CameraController(m_pCamera3D);
		m_pLight = new Light(m_pCamera3D);


		m_pCube = new CubeObject(m_pCamera3D, m_pLight);
		m_pCube->m_transform.m_Translation = { -2.0f, 1.0f, 0.0f };

		m_pQuadObject = new QuadObject(m_pFrameBuffer->getTextureId());

		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_bIsInit = true;
	}

	void FrameBufferScene2::Finalize()
	{
		SAFE_DELETE_SET_NULL(m_pCamera3D);
		SAFE_DELETE_SET_NULL(m_pCameraController);
		SAFE_DELETE_SET_NULL(m_pLight);
		SAFE_DELETE_SET_NULL(m_pQuadObject);
		SAFE_DELETE_SET_NULL(m_pFrameBuffer);
		SAFE_DELETE_SET_NULL(m_pCube);

	}

	void FrameBufferScene2::Tick(float deltaTime)
	{
		

		m_pFrameBuffer->bind();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glEnable(GL_DEPTH_TEST);
		m_pCube->Draw();
		m_pFrameBuffer->unbind();


		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glDisable(GL_DEPTH_TEST);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		m_pQuadObject->Draw();

		
	}

	void FrameBufferScene2::RecompileShader()
	{
		
	}

	void FrameBufferScene2::RenderGUI()
	{
	

	
	}

	void FrameBufferScene2::OnResize(int width, int height)
	{
		m_pCamera3D->aspect = static_cast<float>(width) / height;
	}
}