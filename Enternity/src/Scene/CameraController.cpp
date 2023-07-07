#pragma once
#include "CameraController.h"
#include "ECS/Entity.h"
#include "ECS/CameraComponent.h"
#include "ECS/TransformComponent.h"
#include "Engine/Engine.h"
#include "Engine/Timer.h"
#include "Engine/Event/EventSystem.h"

namespace Enternity
{
	CameraController::CameraController(Entity* sceneCamera)
	{
		m_sceneCamera = sceneCamera;

		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::WindowResize, BIND(CameraController::onWindowResize));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::Tick, BIND(CameraController::tick));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MousePressed, BIND(CameraController::onMousePress));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MouseReleased, BIND(CameraController::onMouseRelease));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MouseMoved, BIND(CameraController::onMouseMove));
		Engine::GetInstance().getEventSystem()->registerEvent(Event::EventType::MouseScroll, BIND(CameraController::onMouseScroll));
	}

	CameraController::~CameraController()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::WindowResize, BIND(CameraController::onWindowResize));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::Tick, BIND(CameraController::tick));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MousePressed, BIND(CameraController::onMousePress));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MouseReleased, BIND(CameraController::onMouseRelease));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MouseMoved, BIND(CameraController::onMouseMove));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(Event::EventType::MouseScroll, BIND(CameraController::onMouseScroll));
	
	}

	void CameraController::onWindowResize(void* data)
	{
		WindowSize ws = *(WindowSize*)(data);
		auto& cameraComponent = m_sceneCamera->getComponent<CameraComponent>();
		cameraComponent.aspect = static_cast<float>(ws.width) / ws.height;
	}

	void CameraController::tick(void* data)
	{
		float deltaTime = *(float*)(data);

		auto& transformComponent = m_sceneCamera->getComponent<TransformComponent>();
		float moveSpeed = m_sceneCamera->getComponent<CameraComponent>().moveSpeed;

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::W))
		{
			transformComponent.moveZAxis(-moveSpeed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::S))
		{
			transformComponent.moveZAxis(moveSpeed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::A))
		{
			transformComponent.moveXAxis(-moveSpeed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::D))
		{
			transformComponent.moveXAxis(moveSpeed * deltaTime);
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
		Mouse mouse = *(Mouse*)data;
		auto& transformComponent = m_sceneCamera->getComponent<TransformComponent>();
		if (mouse.code == MouseCode::ButtonRight)
		{
			m_deltaMousePosX = mouse.x - m_oldMousePosX;
			m_deltaMousePosY = mouse.y - m_oldMousePosY;

			transformComponent.rotateAlongXAxis(m_deltaMousePosY * 0.1f);
			transformComponent.rotateAlongYAxis(m_deltaMousePosX * 0.1f);

			m_oldMousePosX = mouse.x;
			m_oldMousePosY = mouse.y;
		}
	}

	void CameraController::onMouseScroll(void * data)
	{
		float delta = *(float*)data;
		float moveSpeed = m_sceneCamera->getComponent<CameraComponent>().moveSpeed;
		auto& transformComponent = m_sceneCamera->getComponent<TransformComponent>();
		transformComponent.moveZAxis(-delta * moveSpeed * Engine::GetInstance().getTimer()->deltaTime() * 100);
	}
}
