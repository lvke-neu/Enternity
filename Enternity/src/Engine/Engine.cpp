#include "Engine.h"
#include "Engine/ThreadPool.h"
#include "Engine/Log.h"
#include "Graphics/GraphicsSystem.h"

#include "Common/UnitTest.h"

namespace Enternity
{
	void Engine::initialize()
	{
		Log::Init();
		ThreadPool::GetInstance().initialize(4);

		m_graphicsSystem = new GraphicsSystem;
	}

	void Engine::uninitialize()
	{
		ThreadPool::GetInstance().uninitialize();

		SAFE_DELETE_SET_NULL(m_graphicsSystem);
	}

	void Engine::run()
	{
		while (true)
		{
			UnitTest::Test();
		}
	}
}