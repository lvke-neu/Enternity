#include "CameraController.h"
#include "PerspectiveCamera.h"

BEGIN_ENTERNITY

CameraController::CameraController()
{
	TickEventManager::GetInstance().RegisterEvent(this);
}

CameraController::~CameraController()
{
	TickEventManager::GetInstance().UnRegisterEvent(this);
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