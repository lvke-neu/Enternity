#include "CameraController.h"
#include "Core/Event/WindowResizeEvent.h"
#include "Core/Event/TickEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/MouseEvent.h"
#include "Core/Event/EventManager.h"
#include "Camera3D.h"

namespace Enternity
{
	CameraController::CameraController()
	{
		EventManager::GetInstance().registry(EventType::WindowResize, BIND_FUNC(CameraController::onResize));
		EventManager::GetInstance().registry(EventType::Tick, BIND_FUNC(CameraController::tick));
		EventManager::GetInstance().registry(EventType::MousePressed, BIND_FUNC(CameraController::onMousePress));
		EventManager::GetInstance().registry(EventType::MouseReleased, BIND_FUNC(CameraController::onMouseRelease));
		EventManager::GetInstance().registry(EventType::MouseMoved, BIND_FUNC(CameraController::onMouseMove));
	}

	CameraController::~CameraController()
	{
		EventManager::GetInstance().unRegistry(EventType::WindowResize, BIND_FUNC(CameraController::onResize));
		EventManager::GetInstance().unRegistry(EventType::Tick, BIND_FUNC(CameraController::tick));
		EventManager::GetInstance().unRegistry(EventType::MousePressed, BIND_FUNC(CameraController::onMousePress));
		EventManager::GetInstance().unRegistry(EventType::MouseReleased, BIND_FUNC(CameraController::onMouseRelease));
		EventManager::GetInstance().unRegistry(EventType::MouseMoved, BIND_FUNC(CameraController::onMouseMove));
	}

	void CameraController::attachCamera3D(Camera3D* camera3D)
	{
		m_camera3D = camera3D;
	}

	void CameraController::onResize(IEvent* event)
	{
		ENTERNITY_ASSERT(m_camera3D != nullptr && event != nullptr);

		if (event->getEventType() == EventType::WindowResize)
			m_camera3D->setFrustum(Frustum { PI / 6.0f, static_cast<float>(((WindowResizeEvent*)event)->getWidth()) / ((WindowResizeEvent*)event)->getHeight(), 1.0f, 1000.0f });
	}	

	void CameraController::tick(IEvent* event)
	{
		float deltaTime = ((TickEvent*)(event))->getDeltaTime();
		
		if (EventManager::GetInstance().isKeyPressed(KeyCode::W))
		{
			m_camera3D->moveForward(m_moveSpeed * deltaTime);
		}

		if (EventManager::GetInstance().isKeyPressed(KeyCode::S))
		{
			m_camera3D->moveForward(-m_moveSpeed * deltaTime);
		}

		if (EventManager::GetInstance().isKeyPressed(KeyCode::A))
		{
			m_camera3D->moveRight(-m_moveSpeed * deltaTime);
		}

		if (EventManager::GetInstance().isKeyPressed(KeyCode::D))
		{
			m_camera3D->moveRight(m_moveSpeed * deltaTime);
		}
	}

	void CameraController::onMousePress(IEvent* event)
	{
		MousePressedEvent* mousePressedEvent = (MousePressedEvent*)event;
		if (mousePressedEvent->getMouseCode() == MouseCode::ButtonRight)
		{
			m_oldMousePosX = mousePressedEvent->getMouseX();
			m_oldMousePosY = mousePressedEvent->getMouseY();
		}
	}

	void CameraController::onMouseRelease(IEvent* event)
	{
		MousePressedEvent* mousePressedEvent = (MousePressedEvent*)event;
		if (mousePressedEvent->getMouseCode() == MouseCode::ButtonRight)
		{
			m_deltaMousePosX = 0;
			m_deltaMousePosY = 0;
		}
	}

	void CameraController::onMouseMove(IEvent* event)
	{
		MousePressedEvent* mousePressedEvent = (MousePressedEvent*)event;
		if (mousePressedEvent->getMouseCode() == MouseCode::ButtonRight)
		{
			m_deltaMousePosX = mousePressedEvent->getMouseX() - m_oldMousePosX;
			m_deltaMousePosY = mousePressedEvent->getMouseY() - m_oldMousePosY;

			m_camera3D->rotateAlongXAxis(m_deltaMousePosY * 0.1f);
			m_camera3D->rotateAlongYAxis(m_deltaMousePosX * 0.1f);

			m_oldMousePosX = mousePressedEvent->getMouseX();
			m_oldMousePosY = mousePressedEvent->getMouseY();
		}
	}
}