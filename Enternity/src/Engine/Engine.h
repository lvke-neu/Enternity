#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class Timer;
	class RenderView;
	class GraphicsSystem;
	class EventSystem;
	class SceneManager;
	class Engine
	{
		SINGLETON(Engine);
		PRIVATE(Engine);
	public:
		void initialize();
		void uninitialize();
		void run();
	public:
		GraphicsSystem* getGraphicsSystem();
		EventSystem* getEventSystem();
		SceneManager* getSceneManager();
	private:
		GraphicsSystem* m_graphicsSystem{ nullptr };
		EventSystem* m_eventSystem{ nullptr };
		RenderView* m_renderView{ nullptr };
		SceneManager* m_sceneManager{ nullptr };
		Timer* m_timer{ nullptr };
	};

	inline GraphicsSystem* Engine::getGraphicsSystem()
	{
		return m_graphicsSystem;
	}

	inline EventSystem* Engine::getEventSystem()
	{
		return m_eventSystem;
	}

	inline SceneManager* Engine::getSceneManager()
	{
		return m_sceneManager;
	}
}