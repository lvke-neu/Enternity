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
    public:
        static void Resize(GLFWwindow* window, int width, int height);
    private:
        GLFWwindow* m_context;
        FrameTimer m_timer;
    };
}

