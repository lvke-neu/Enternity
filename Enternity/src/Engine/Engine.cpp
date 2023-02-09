#include "Engine.h"
#include "Core/Log/Log.h"
#include "Platform/Window/OpenglWindow.h"
#include "Function/Render/RenderSystem.h"
#include "Core/ExecutionTimer/ExecutionTimer.h"

namespace Enternity
{
	void Engine::initialize()
	{
		ExecutionTimer executionTimer("The time of engine intialization");

		Log::Init();

		OpenglWindow::OpenglWindowDescription openglWindowDesc;
		openglWindowDesc.Width = 1200;
		openglWindowDesc.Height = 600;
		openglWindowDesc.Title = "Enternity Engine v0.004";
		m_window = new OpenglWindow(openglWindowDesc);

		RenderSystem::GetInstance().initialize();

		LOG_INFO("Engine initialization");
	}

	void Engine::uninitialize()
	{
		RenderSystem::GetInstance().uninitialize();
		SAFE_DELETE_SET_NULL(m_window);

		LOG_INFO("Engine uninitialization");
	}

	void Engine::run()
	{	
		ENTERNITY_ASSERT(m_window != nullptr);
		while (!m_window->windowShouldClose())
		{
			RenderSystem::GetInstance().clear(Vector4f::DARK_COLOR);
			
			m_window->update();
		}
	}
}