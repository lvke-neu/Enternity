#pragma once
#include "CameraController.h"
#include "ECS/Entity.h"
#include "ECS/CameraComponent.h"
#include "ECS/TransformComponent.h"
#include "Engine/Engine.h"
#include "Engine/Event/EventSystem.h"

namespace Enternity
{
	CameraController::CameraController(Entity* sceneCamera)
	{
		m_sceneCamera = sceneCamera;

		Engine::GetInstance().getEventSystem()->registerEvent(EventType::WindowResize, BIND(CameraController::onWindowResize));
		Engine::GetInstance().getEventSystem()->registerEvent(EventType::Tick, BIND(CameraController::tick));
		Engine::GetInstance().getEventSystem()->registerEvent(EventType::MousePressed, BIND(CameraController::onMousePress));
		Engine::GetInstance().getEventSystem()->registerEvent(EventType::MouseReleased, BIND(CameraController::onMouseRelease));
		Engine::GetInstance().getEventSystem()->registerEvent(EventType::MouseMoved, BIND(CameraController::onMouseMove));
	}

	CameraController::~CameraController()
	{
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::WindowResize, BIND(CameraController::onWindowResize));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::Tick, BIND(CameraController::tick));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::MousePressed, BIND(CameraController::onMousePress));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::MouseReleased, BIND(CameraController::onMouseRelease));
		Engine::GetInstance().getEventSystem()->unRegisterEvent(EventType::MouseMoved, BIND(CameraController::onMouseMove));
	
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

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::W))
		{
			transformComponent.moveZAxis(-m_moveSpeed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::S))
		{
			transformComponent.moveZAxis(m_moveSpeed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::A))
		{
			transformComponent.moveXAxis(-m_moveSpeed * deltaTime);
		}

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::D))
		{
			transformComponent.moveXAxis(m_moveSpeed * deltaTime);
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

			transformComponent.rotateAlongXAxis(m_deltaMousePosY * 0.01f);
			transformComponent.rotateAlongYAxis(m_deltaMousePosX * 0.01f);

			m_oldMousePosX = mouse.x;
			m_oldMousePosY = mouse.y;
		}
	}
}
