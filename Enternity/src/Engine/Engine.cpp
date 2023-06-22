#include "Engine.h"
#include "Engine/ThreadPool.h"
#include "Engine/Log.h"
#include "Graphics/GraphicsSystem.h"
#include "Event/EventSystem.h"
#include "Scene/SceneManager.h"
#include "RenderView.h"
#include "Timer.h"
#include <glad/glad.h>

namespace Enternity
{
	void Engine::initialize()
	{
		Log::Init();
		ThreadPool::GetInstance().initialize(4);

		m_graphicsSystem = new GraphicsSystem;
		m_eventSystem = new EventSystem;
		m_sceneManager = new SceneManager;
		m_renderView = new RenderView(1500, 768, "v0.004");
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
		m_timer->Reset();
		while (!m_renderView->windowShouldClose())
		{
			CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));


			float deltaTime = m_timer->DeltaTime();
			m_eventSystem->dispatchEvent(EventType::Tick, &deltaTime);

			m_timer->Tick();

			m_sceneManager->onUpdateTime(deltaTime);
			


			m_renderView->swapBuffers();
		}
	}
}