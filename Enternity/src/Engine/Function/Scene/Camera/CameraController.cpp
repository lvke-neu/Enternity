#include "CameraController.h"
#include "Core/Event/WindowResizeEvent.h"
#include "Core/Event/EventManager.h"
#include "Camera3D.h"

namespace Enternity
{
	CameraController::CameraController()
	{
		EventManager::GetInstance().registry(EventType::WindowResize, BIND_FUNC(CameraController::onResize));
	}

	CameraController::~CameraController()
	{
		EventManager::GetInstance().unRegistry(EventType::WindowResize, BIND_FUNC(CameraController::onResize));
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
}