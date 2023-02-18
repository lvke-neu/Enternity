/***************************************************************************************
Author: lvke
Date:2023/2/17 22:45
Description:
Camera Controller
****************************************************************************************/
#pragma once

namespace Enternity
{
	class Camera3D;
	class IEvent;
	class CameraController
	{
	public:
		CameraController();
		~CameraController();

		void attachCamera3D(Camera3D* camera3D);
		float getMoveSpeed()
		{
			return m_moveSpeed;
		}
		void setMoveSpeed(float moveSpeed)
		{
			m_moveSpeed = moveSpeed;
		}
	private:
		void onResize(IEvent* event);
		void tick(IEvent* event);
		void onMousePress(IEvent* event);
		void onMouseRelease(IEvent* event);
		void onMouseMove(IEvent* event);
	private:
		Camera3D* m_camera3D{ nullptr };
		float m_moveSpeed = 10.0f;

		float m_oldMousePosX;
		float m_oldMousePosY;
		float m_deltaMousePosX = 0;
		float m_deltaMousePosY = 0;
	};
}