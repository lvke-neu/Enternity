#include "CameraController.h"
#include "Camera3D.h"

namespace Enternity
{
	CameraController::CameraController(Camera3D* camera) : m_pCamera3D(camera)
	{
		InputEventManager::GetInstance().RegisterEvent(this);
		TickEventManager::GetInstance().RegisterEvent(this);
	}

	CameraController::~CameraController()
	{
		InputEventManager::GetInstance().UnRegisterEvent(this);
		TickEventManager::GetInstance().UnRegisterEvent(this);
	}

	void CameraController::onMousePress(MouseState mouseState)
	{
		if (mouseState.mouseButton == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_oldMousePosX = mouseState.x;
			m_oldMousePosY = mouseState.y;
		}
	}

	void CameraController::onMouseRelease(MouseState mouseState)
	{
		if (mouseState.mouseButton == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_deltaMousePosX = 0;
			m_deltaMousePosY = 0;
		}
	}

	void CameraController::onMouseMove(MouseState mouseState)
	{
		if (mouseState.mouseButton == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_deltaMousePosX = mouseState.x - m_oldMousePosX;
			m_deltaMousePosY = mouseState.y - m_oldMousePosY;


			m_pCamera3D->m_transform.RotateAlongXAxis(m_deltaMousePosY * 0.001f);
			m_pCamera3D->m_transform.RotateAlongYAxis(m_deltaMousePosX  * 0.001f);

			m_oldMousePosX = mouseState.x;
			m_oldMousePosY = mouseState.y;
		}
	}

	void CameraController::onMouseWheel(MouseState mouseState)
	{
		//m_CameraEntity.GetComponent<TransformComponent>().MoveZAxis(-mouseState.delta * m_CameraEntity.GetComponent<CameraComponent>().m_MoveSpeed * Engine::GetInstance().GetDeltaTime());
	}

	void CameraController::tick(float deltaTime)
	{

		float moveSpeed = 10.0f;

		if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_W))
		{
			m_pCamera3D->m_transform.MoveZAxis(-deltaTime * moveSpeed);
		}

		if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_S))
		{
			m_pCamera3D->m_transform.MoveZAxis(deltaTime * moveSpeed);
		}

		if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_A))
		{
			m_pCamera3D->m_transform.MoveXAxis(-deltaTime * moveSpeed);
		}

		if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_D))
		{
			m_pCamera3D->m_transform.MoveXAxis(deltaTime * moveSpeed);
		}
	}

}