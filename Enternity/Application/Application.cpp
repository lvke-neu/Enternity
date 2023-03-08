#include "Application.h"
#include "Engine.h"

namespace Enternity
{
	bool Application::Initialize()
    {
        return Engine::GetInstance().Initialize();
    }

    void Application::Finalize()
    {
		Engine::GetInstance().Finalize();
    }

    void Application::Run()
    {
		while (!Engine::GetInstance().IsQuit())
		{
			Engine::GetInstance().Tick();
		}
    }
}