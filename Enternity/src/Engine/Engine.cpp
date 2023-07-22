#include "Engine.h"
#include "Engine/ThreadPool.h"
#include "Engine/Log.h"
#include "Graphics/GraphicsSystem.h"
#include "Event/EventSystem.h"
#include "Pick/PickSystem.h"
#include "Scene/SceneManager.h"
#include "BlobLoaderManager.h"
#include "RenderView.h"
#include "Timer.h"
#include "NativeFileSystem.h"
#include "AssetLoader.h"

namespace Enternity
{
	void Engine::initialize()
	{
		Log::Init();
		ThreadPool::GetInstance().initialize(8);

		m_timer = new Timer;
		m_renderView = new RenderView(1920, 900, "v0.004");
		m_eventSystem = new EventSystem;
		m_blobLoaderManager = new BlobLoaderManager;
		m_nativeFileSystem = new NativeFileSystem;
		m_assetLoader = new AssetLoader;
		m_graphicsSystem = new GraphicsSystem;
		m_pickSystem = new PickSystem;
		m_sceneManager = new SceneManager;
		
	}

	void Engine::uninitialize()
	{
		ThreadPool::GetInstance().uninitialize();

		SAFE_DELETE_SET_NULL(m_sceneManager);
		SAFE_DELETE_SET_NULL(m_pickSystem);
		SAFE_DELETE_SET_NULL(m_graphicsSystem);
		SAFE_DELETE_SET_NULL(m_assetLoader);
		SAFE_DELETE_SET_NULL(m_nativeFileSystem);
		SAFE_DELETE_SET_NULL(m_blobLoaderManager);
		SAFE_DELETE_SET_NULL(m_eventSystem);
		SAFE_DELETE_SET_NULL(m_renderView);
		SAFE_DELETE_SET_NULL(m_timer);
		
	}

	void Engine::run()
	{
		m_timer->reset();
		while (!m_renderView->windowShouldClose())
		{
			m_renderView->pollEvents();

			m_timer->tick();
			float deltaTime = m_timer->deltaTime();
			m_eventSystem->dispatchEvent(Event::EventType::Tick, &deltaTime);

			m_sceneManager->tick(deltaTime);
			m_renderView->swapBuffers();
		}
	}
}