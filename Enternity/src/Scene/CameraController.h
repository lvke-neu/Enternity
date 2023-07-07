#pragma once

namespace Enternity
{
	class Entity;
	class CameraController
	{
	public:
		CameraController(Entity* sceneCamera);
		~CameraController();
	private:
		void onWindowResize(void* data);
		void tick(void* data);
		void onMousePress(void* data);
		void onMouseRelease(void* data);
		void onMouseMove(void* data);
		void onMouseScroll(void* data);
	private:
		Entity* m_sceneCamera{ nullptr };

		float m_oldMousePosX;
		float m_oldMousePosY;
		float m_deltaMousePosX = 0;
		float m_deltaMousePosY = 0;
	};
}