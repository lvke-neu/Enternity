#include "Engine.h"
#include "Core/Log/Log.h"
#include "Platform/Window/OpenglWindow.h"
#include "Function/Render/RenderSystem.h"
#include "Core/Timer/ExecutionTimer.h"
#include "Core/Timer/FrameTimer.h"

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

		//RenderSystem init
		RenderSystem::GetInstance().initialize();

		//timer init
		m_timer = new FrameTimer;

		LOG_INFO("Engine initialization");
	}

	void Engine::uninitialize()
	{
		RenderSystem::GetInstance().uninitialize();
		SAFE_DELETE_SET_NULL(m_window);
		SAFE_DELETE_SET_NULL(m_timer);

		LOG_INFO("Engine uninitialization");
	}

	void Engine::run()
	{	
		ENTERNITY_ASSERT(m_window != nullptr);
		ENTERNITY_ASSERT(m_timer != nullptr);

		m_timer->Reset();

		while (!m_window->windowShouldClose())
		{
			m_timer->Tick();
			
			//print fps every one sceond
			//TODO:remove, show fps in imgui panel
			static float sumDeltaTime = 0;
			sumDeltaTime += m_timer->DeltaTime();
			if (sumDeltaTime > 1.0f)
			{
				m_window->setTitle(("FPS:" + std::to_string(1.0f / m_timer->DeltaTime())).c_str());
				sumDeltaTime = 0.0f;
			}
				
			RenderSystem::GetInstance().clear(Vector4f::DARK_COLOR);
			
			m_window->update();
		}
	}
}