#include "Application.h"
#include "Core/Log/Log.h"
#include "Core/Event/InputEventManager.h"
#include "Core/Event/TickEventManager.h"
#include "GUI/GUIRender.h"
#include "Scene/SceneManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enternity
{
	void Application::Initialize(int WindowWidth, int WindowHeight, const char* WindowTitle)
    {
		Log::Init();

		if (!glfwInit())
		{

			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		m_context = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, nullptr, nullptr);
		if (!m_context)
		{
			return;
		}
		glfwMakeContextCurrent(m_context);
		//don't Limit frame count
		glfwSwapInterval(0);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return;
		}

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, WindowWidth, WindowHeight);
		glfwSetWindowSizeCallback(m_context, Resize);
		glfwSetKeyCallback(m_context, KeyEvent);
		glfwSetMouseButtonCallback(m_context, MouseButtonEvent);
		glfwSetCursorPosCallback(m_context, MouseMoveEvent);

		SceneManager::GetInstance().Initialize();
		GUIRender::GetInstance().Initialize(m_context);

		LOG_TRACE((char*)glGetString(GL_VERSION));
		LOG_TRACE((char*)glGetString(GL_VENDOR));
		LOG_TRACE((char*)glGetString(GL_RENDERER));

		//cull face
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		return;
    }

    void Application::Finalize()
    {
		SceneManager::GetInstance().Finalize();
		GUIRender::GetInstance().Finalize();
		glfwTerminate();
    }

    void Application::Run()
    {
		m_timer.Reset();
		while (!glfwWindowShouldClose(m_context))
		{
			m_timer.Tick();
			TickEventManager::GetInstance().NotifyTick(m_timer.DeltaTime());
			glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			SceneManager::GetInstance().Tick(m_timer.DeltaTime());
			GUIRender::GetInstance().Tick();
			glfwSwapBuffers(m_context);
			glfwPollEvents();
		}
    }

	void Application::Resize(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		SceneManager::GetInstance().OnResize(width, height);
	}

	void Application::KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_RELEASE)
		{
			//LOG_INFO(std::to_string(key) + " release");
			InputEventManager::GetInstance().NotifyKeyRelease((Enternity::Keyboard)key);
		}

		if (action == GLFW_PRESS)
		{
			//LOG_INFO(std::to_string(key) + " press");
			InputEventManager::GetInstance().NotifyKeyPress((Enternity::Keyboard)key);
		}
	}

	void Application::MouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_RELEASE)
		{
			//LOG_INFO(std::to_string(button) + " release");
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			InputEventManager::GetInstance().NotifyMouseRelease({ (MouseButton)button, (int)x, (int)y, 0 });
		}

		if (action == GLFW_PRESS)
		{
			//LOG_INFO(std::to_string(button) + " press");
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			InputEventManager::GetInstance().NotifyMousePress({ (MouseButton)button, (int)x, (int)y, 0 });
		}
	}

	void Application::MouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
	{
		//LOG_INFO("mouse pos:" + std::to_string(xpos) + "," + std::to_string(ypos));

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			InputEventManager::GetInstance().NotifyMouseMove({ (MouseButton)GLFW_MOUSE_BUTTON_LEFT, (int)xpos, (int)ypos, 0 });
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			InputEventManager::GetInstance().NotifyMouseMove({ (MouseButton)GLFW_MOUSE_BUTTON_RIGHT, (int)xpos, (int)ypos, 0 });
		}
	}
}