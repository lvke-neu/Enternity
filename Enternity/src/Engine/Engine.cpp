#include "Engine.h"
#include "Core/Timer/ExecutionTimer.h"
#include "Core/Timer/FrameTimer.h"
#include "Core/ThreadPool/ThreadPool.h"
#include "Platform/Window/OpenglWindow.h"
#include "Function/Render/RenderSystem.h"
#include "Function/Ui/UiRenderSystem.h"
#include "Function/Scene/SceneManager.h"

namespace Enternity
{
	void Engine::initialize()
	{
		//debug execution timer
		ExecutionTimer executionTimer("The time of engine intialization");
		
		//log init
		Log::Init();
		
		//opengl init
		OpenglWindow::OpenglWindowDescription openglWindowDesc;
		openglWindowDesc.Width = 1200;
		openglWindowDesc.Height = 600;
		openglWindowDesc.Title = "Enternity Engine v0.004";
		m_window = new OpenglWindow(openglWindowDesc);

		//SceneManager init
		SceneManager::GetInstance().initialize();

		//RenderSystem init
		RenderSystem::GetInstance().initialize();

		//UiRenderSystem init
		UiRenderSystem::GetInstance().initialize(m_window);

		//timer init
		m_timer = new FrameTimer;

		//ThreadPool init
		ThreadPool::GetInstance().initialize(8);

		//resize the window in the begin
		OpenglWindow::Resize(m_window->getContext(), openglWindowDesc.Width, openglWindowDesc.Height);

		LOG_INFO("Engine initialization");
	}

	void Engine::uninitialize()
	{
		SceneManager::GetInstance().uninitialize();
		RenderSystem::GetInstance().uninitialize();
		UiRenderSystem::GetInstance().uninitialize();
		ThreadPool::GetInstance().uninitialize();
		SAFE_DELETE_SET_NULL(m_window);
		SAFE_DELETE_SET_NULL(m_timer);

		LOG_INFO("Engine uninitialization");
	}

	void Engine::run()
	{	
		ENTERNITY_ASSERT(m_window != nullptr && m_timer != nullptr);

		m_timer->Reset();

		while (!m_window->windowShouldClose())
		{
			m_timer->Tick();
			
			tick(m_timer->DeltaTime());

			m_window->swapBuffers(m_timer->DeltaTime());
		}
	}

	void Engine::tick(float deltaTime)
	{
		SceneManager::GetInstance().tick(deltaTime);
 		RenderSystem::GetInstance().tick();
		//draw ui at the end
		UiRenderSystem::GetInstance().tick();
	}
}