#pragma once
#include "Core/Timer/FrameTimer.h"

struct GLFWwindow;
namespace Enternity
{
    class Application
    {
    public:
		void Initialize(int WindowWidth, int WindowHeight, const char* WindowTitle);
		void Finalize();
		void Run();
    private:
        GLFWwindow* m_context;
        FrameTimer m_timer;
    };
}

