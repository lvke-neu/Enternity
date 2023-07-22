#include "Engine.h"
#include "Log.h"
#include "ThreadPool.h"
#include "Timer.h"
#include "RenderView.h"
#include "EventSystem.h"
#include "BlobLoaderManager.h"
#include "NativeFileSystem.h"
#include "AssetLoader.h"
#include "Graphics/GraphicsSystem.h"
#include "Pick/PickSystem.h"
#include "Scene/SceneManager.h"

namespace Enternity
{
	void Engine::initialize()
	{
		Log::Init();
		ThreadPool::GetInstance().initialize(8);

		m_renderView = new RenderView;
		m_timer = new Timer;
		m_eventSystem = new EventSystem;
		m_blobLoaderManager = new BlobLoaderManager;
		m_nativeFileSystem = new NativeFileSystem;
		m_assetLoader = new AssetLoader;
		m_graphicsSystem = new GraphicsSystem;
		m_pickSystem = new PickSystem;
		m_sceneManager = new SceneManager;

		m_renderView->setWindowProperty(1900, 900, "Version:0.004,Author:lvke", "texture://assets/textures/logo/windowlogo.png");
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