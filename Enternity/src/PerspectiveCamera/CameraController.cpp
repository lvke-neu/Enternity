#include "CameraController.h"
#include "PerspectiveCamera.h"

BEGIN_ENTERNITY

CameraController::CameraController()
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

		PerspectiveCamera::GetInstance().RotateAlongXAxis(m_deltaMousePosY * 0.01f);
		PerspectiveCamera::GetInstance() .RotateAlongYAxis(m_deltaMousePosX * 0.01f);

		m_oldMousePosX = mouseState.x;
		m_oldMousePosY = mouseState.y;
	}
}

void CameraController::onMouseWheel(MouseState mouseState)
{
	/*Singleton<PerspectiveCamera>::GetInstance().moveZAxis(mouseState.delta * m_moveSpeed * 0.001f);*/
}

void CameraController::tick(float deltaTime)
{
	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_W))
	{
		PerspectiveCamera::GetInstance().MoveZAxis(-deltaTime * m_MoveSpeed);
	}

	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_S))
	{
		PerspectiveCamera::GetInstance().MoveZAxis(deltaTime * m_MoveSpeed);
	}

	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_A))
	{
		PerspectiveCamera::GetInstance().MoveXAxis(-deltaTime * m_MoveSpeed);
	}

	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_D))
	{
		PerspectiveCamera::GetInstance().MoveXAxis(deltaTime * m_MoveSpeed);
	}
}

END_ENTERNITY