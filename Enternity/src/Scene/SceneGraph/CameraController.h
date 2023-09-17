#pragma once
#include "Engine/Component.h"

namespace Enternity
{
	class CameraController : public Component
	{
		RTTR_ENABLE(Component);
	public:
		CameraController();
		~CameraController();
	public:
		GET_CLASS_NAME(CameraController);
	public:
		GET_SET(float, speed);
	private:
		void tick(void* data);
		void onMousePress(void* data);
		void onMouseRelease(void* data);
		void onMouseMove(void* data);
		void onMouseScroll(void* data);
	private:
		float m_speed;
	
		float m_oldMousePosX;
		float m_oldMousePosY;
		float m_deltaMousePosX;
		float m_deltaMousePosY;
	};
}