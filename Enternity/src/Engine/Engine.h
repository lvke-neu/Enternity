#pragma once
#include "Common/Macro.h"

namespace Enternity
{
	class Timer;
	class RenderView;
	class GraphicsSystem;
	class EventSystem;
	class PickSystem;
	class SceneManager;
	class BlobLoaderManager;
	class Engine
	{
		SINGLETON(Engine);
		PRIVATE(Engine);
	public:
		void initialize();
		void uninitialize();
		void run();
		Timer* getTimer();
	public:
		GraphicsSystem* getGraphicsSystem();
		EventSystem* getEventSystem();
		PickSystem* getPickSystem();
		SceneManager* getSceneManager();
		RenderView* getRenderView();
		BlobLoaderManager* getBlobLoaderManager();
	private:
		GraphicsSystem* m_graphicsSystem{ nullptr };
		EventSystem* m_eventSystem{ nullptr };
		PickSystem* m_pickSystem{ nullptr };
		RenderView* m_renderView{ nullptr };
		SceneManager* m_sceneManager{ nullptr };
		BlobLoaderManager* m_blobLoaderManager{ nullptr };
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

	inline PickSystem* Engine::getPickSystem()
	{
		return m_pickSystem;
	}

	inline SceneManager* Engine::getSceneManager()
	{
		return m_sceneManager;
	}

	inline BlobLoaderManager* Engine::getBlobLoaderManager()
	{
		return m_blobLoaderManager;
	}

	inline RenderView* Engine::getRenderView()
	{
		return m_renderView;
	}

	inline Timer* Engine::getTimer()
	{
		return m_timer;
	}
}