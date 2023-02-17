#include "CameraController.h"
#include "Core/Event/WindowResizeEvent.h"
#include "Core/Event/KeyEvent.h"
#include "Core/Event/EventManager.h"
#include "Camera3D.h"

namespace Enternity
{
	CameraController::CameraController()
	{
		EventManager::GetInstance().registry(EventType::WindowResize, BIND_FUNC(CameraController::onResize));
		EventManager::GetInstance().registry(EventType::KeyPressed, BIND_FUNC(CameraController::onKeyPressed));
	}

	CameraController::~CameraController()
	{
		EventManager::GetInstance().unRegistry(EventType::WindowResize, BIND_FUNC(CameraController::onResize));
		EventManager::GetInstance().unRegistry(EventType::KeyPressed, BIND_FUNC(CameraController::onKeyPressed));
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
	
	void CameraController::onKeyPressed(IEvent* event)
	{
		ENTERNITY_ASSERT(m_camera3D != nullptr && event != nullptr);

		if (event->getEventType() == EventType::KeyPressed)
		{
			KeyCode keyCode = ((KeyPressedEvent*)(event))->getKeyCode();
			Vector3f pos = m_camera3D->getPosition();
			if (keyCode == KeyCode::W)
			{
				pos.z -= 1;
				
			}
			else if (keyCode == KeyCode::S)
			{
				pos.z += 1;
			}
			else if (keyCode == KeyCode::A)
			{
				pos.x -= 1;
			}
			else if (keyCode == KeyCode::D)
			{
				pos.x += 1;
			}

			m_camera3D->setPosition(pos);	
		}
	}
}