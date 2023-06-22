#include "Engine.h"
#include "Engine/ThreadPool.h"
#include "Engine/Log.h"
#include "Graphics/GraphicsSystem.h"
#include "Event/EventSystem.h"
#include "Scene/SceneManager.h"
#include "RenderView.h"
#include "Timer.h"

namespace Enternity
{
	void Engine::initialize()
	{
		Log::Init();
		ThreadPool::GetInstance().initialize(4);

		m_renderView = new RenderView(1500, 768, "v0.004");
		m_graphicsSystem = new GraphicsSystem;
		m_eventSystem = new EventSystem;
		m_sceneManager = new SceneManager;
		m_timer = new Timer;
	}

	void Engine::uninitialize()
	{
		ThreadPool::GetInstance().uninitialize();

		SAFE_DELETE_SET_NULL(m_sceneManager);
		SAFE_DELETE_SET_NULL(m_graphicsSystem);
		SAFE_DELETE_SET_NULL(m_eventSystem);
		SAFE_DELETE_SET_NULL(m_renderView);
		SAFE_DELETE_SET_NULL(m_timer);
	}

	void Engine::run()
	{
		m_timer->reset();
		while (!m_renderView->windowShouldClose())
		{
			m_timer->tick();
			float deltaTime = m_timer->deltaTime();
			m_eventSystem->dispatchEvent(EventType::Tick, &deltaTime);

			m_sceneManager->tick(deltaTime);
			m_renderView->swapBuffers();
		}
	}
}