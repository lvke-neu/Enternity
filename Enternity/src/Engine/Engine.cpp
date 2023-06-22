#include "Engine.h"
#include "Engine/ThreadPool.h"
#include "Engine/Log.h"
#include "Graphics/GraphicsSystem.h"
#include "Event/EventSystem.h"
#include "RenderView.h"
#include "Timer.h"

namespace Enternity
{
	void Engine::initialize()
	{
		Log::Init();
		ThreadPool::GetInstance().initialize(4);

		m_graphicsSystem = new GraphicsSystem;
		m_eventSystem = new EventSystem;
		m_renderView = new RenderView(1024, 768, "v0.004");
		m_timer = new Timer;
	}

	void Engine::uninitialize()
	{
		ThreadPool::GetInstance().uninitialize();

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
			float deltaTime = m_timer->DeltaTime();
			getEventSystem()->dispatchEvent(EventType::Tick, &deltaTime);

			m_timer->Tick();
			//CHECK_GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			//CHECK_GL_CALL((glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT)));
			m_renderView->swapBuffers();
		}
	}
}