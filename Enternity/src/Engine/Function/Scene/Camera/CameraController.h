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
	private:
		void onResize(IEvent* event);
	private:
		Camera3D* m_camera3D{ nullptr };
	};
}