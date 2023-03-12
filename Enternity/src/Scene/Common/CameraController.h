/***************************************************************************************
Author: lvke
Date:2023/1/2 15:57
Description:
Camera Controller
****************************************************************************************/
#pragma once
#include "Core/Event/InputEventManager.h"
#include "Core/Event/TickEventManager.h"

namespace Enternity
{
	class Camera3D;
	class CameraController : public InputEvent, public TickEvent
	{
	public:
		CameraController(Camera3D* camera);
		~CameraController();
		CameraController(const CameraController&) = delete;
		CameraController& operator=(const CameraController&) = delete;

		void Pause()
		{
			InputEventManager::GetInstance().UnRegisterEvent((this));
			TickEventManager::GetInstance().UnRegisterEvent(this);
		}
		void Start()
		{
			InputEventManager::GetInstance().RegisterEvent((this));
			TickEventManager::GetInstance().RegisterEvent(this);
		}
	public:
		virtual void onMousePress(MouseState mouseState) override;
		virtual void onMouseRelease(MouseState mouseState) override;
		virtual void onMouseMove(MouseState mouseState) override;
		virtual void onMouseWheel(MouseState mouseState) override;

		virtual void tick(float deltaTime) override;
	private:
		int m_oldMousePosX;
		int m_oldMousePosY;
		int m_deltaMousePosX = 0;
		int m_deltaMousePosY = 0;

		Camera3D* m_pCamera3D{ nullptr };
	};

}