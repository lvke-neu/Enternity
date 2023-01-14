#include "CameraController.h"
#include "ECS/Component/Component.h"

BEGIN_ENTERNITY

CameraController::CameraController(Entity cameraEntity):
	m_CameraEntity(cameraEntity)
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

		
		m_CameraEntity.GetComponent<TransformComponent>().RotateAlongXAxis(m_deltaMousePosY * 0.01f);
		m_CameraEntity.GetComponent<TransformComponent>().RotateAlongYAxis(m_deltaMousePosX * 0.01f);

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
	auto moveSpeed = m_CameraEntity.GetComponent<CameraComponent>().m_MoveSpeed;

	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_W))
	{
		m_CameraEntity.GetComponent<TransformComponent>().MoveZAxis(-deltaTime * moveSpeed);
	}

	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_S))
	{
		m_CameraEntity.GetComponent<TransformComponent>().MoveZAxis(deltaTime * moveSpeed);
	}

	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_A))
	{
		m_CameraEntity.GetComponent<TransformComponent>().MoveXAxis(-deltaTime * moveSpeed);
	}

	if (InputEventManager::GetInstance().IsKeyPress(GLFW_KEY_D))
	{
		m_CameraEntity.GetComponent<TransformComponent>().MoveXAxis(deltaTime * moveSpeed);
	}
}

END_ENTERNITY