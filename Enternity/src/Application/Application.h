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
		static void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods);
		static void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos);
    private:
        GLFWwindow* m_context;
        FrameTimer m_timer;
    };
}

