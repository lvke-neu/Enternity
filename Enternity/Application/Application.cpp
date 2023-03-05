#include "Application.h"
#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enternity
{

	Application::Application(const ApplicationDescription& desc):
		m_appDescription(desc)
	{

	}

	bool Application::Initialize()
    {
		if (!glfwInit())
		{

			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		m_context = glfwCreateWindow(m_appDescription.Width, m_appDescription.Height, m_appDescription.Title, nullptr, nullptr);
		if (!m_context)
		{
			return false;
		}
		glfwMakeContextCurrent(m_context);
		//don't Limit frame count
		glfwSwapInterval(0);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return false;
		}

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, m_appDescription.Width, m_appDescription.Height);

		Engine::GetInstance().Initialize();

        return true;
    }

    void Application::Finalize()
    {
		Engine::GetInstance().Finalize();
		glfwTerminate();
    }

    void Application::Run()
    {
		while (!glfwWindowShouldClose(m_context))
		{
			glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Engine::GetInstance().Tick();

			glfwSwapBuffers(m_context);
			glfwPollEvents();
		}
    }
}