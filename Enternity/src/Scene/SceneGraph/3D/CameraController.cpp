#include "CameraController.h"
#include "Node3D.h"
#include "Engine/Engine.h"
#include "Engine/EventSystem.h"

namespace Enternity
{
	CameraController::CameraController() :
		m_speed(10.0f),
		m_oldMousePosX(0.0f),
		m_oldMousePosY(0.0f),
		m_deltaMousePosX(0.0f),
		m_deltaMousePosY(0.0f)
	{
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::Tick, BIND(CameraController::tick));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MousePressed, BIND(CameraController::onMousePress));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MouseReleased, BIND(CameraController::onMouseRelease));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MouseMoved, BIND(CameraController::onMouseMove));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MouseScroll, BIND(CameraController::onMouseScroll));
	}

	CameraController::~CameraController()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::Tick, BIND(CameraController::tick));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MousePressed, BIND(CameraController::onMousePress));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MouseReleased, BIND(CameraController::onMouseRelease));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MouseMoved, BIND(CameraController::onMouseMove));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MouseScroll, BIND(CameraController::onMouseScroll));
	}

	void CameraController::tick(void* data)
	{
		if (!m_enable)
		{
			return;
		}

		float deltaTime = *(float*)(data);

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::W))
		{
			getNode<Node3D>()->getTransform().moveZAxis(-m_speed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::S))
		{
			getNode<Node3D>()->getTransform().moveZAxis(m_speed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::A))
		{
			getNode<Node3D>()->getTransform().moveXAxis(-m_speed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::D))
		{
			getNode<Node3D>()->getTransform().moveXAxis(m_speed * deltaTime);
		}
	}

	void CameraController::onMousePress(void* data)
	{
		Mouse mouse = *(Mouse*)data;

		if (mouse.code == MouseCode::ButtonRight)
		{
			m_oldMousePosX = mouse.x;
			m_oldMousePosY = mouse.y;
		}
	}

	void CameraController::onMouseRelease(void* data)
	{
		Mouse mouse = *(Mouse*)data;

		if (mouse.code == MouseCode::ButtonRight)
		{
			m_deltaMousePosX = 0;
			m_deltaMousePosY = 0;
		}
	}

	void CameraController::onMouseMove(void* data)
	{
		if (!m_enable)
		{
			return;
		}

		Mouse mouse = *(Mouse*)data;
	
		if (mouse.code == MouseCode::ButtonRight)
		{
			m_deltaMousePosX = mouse.x - m_oldMousePosX;
			m_deltaMousePosY = mouse.y - m_oldMousePosY;

			getNode<Node3D>()->getTransform().rotateAlongXAxis(m_deltaMousePosY * 0.1f);
			getNode<Node3D>()->getTransform().rotateAlongYAxis(m_deltaMousePosX * 0.1f);

			m_oldMousePosX = mouse.x;
			m_oldMousePosY = mouse.y;
		}
	}

	void CameraController::onMouseScroll(void * data)
	{
		if (!m_enable)
		{
			return;
		}

		float delta = *(float*)data;
		getNode<Node3D>()->getTransform().moveZAxis(-delta * m_speed);
	}

	RTTR_REGISTRATION
	{
		rttr::registration::class_<CameraController>("CameraController")
			.constructor<>()
			(
				rttr::policy::ctor::as_raw_ptr
			)
			.property("speed", &CameraController::get_speed, &CameraController::set_speed);
	}
}