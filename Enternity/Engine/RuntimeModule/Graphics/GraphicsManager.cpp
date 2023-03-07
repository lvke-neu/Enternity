#include "GraphicsManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enternity
{
	const int WindowWidth = 1200;
	const int WindowHeight = 800;
	const char* WindowTitle = "hahaha";

	bool GraphicsManager::Initialize() 
	{
		if (!glfwInit())
		{

			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		m_context = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, nullptr, nullptr);
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
		glViewport(0, 0, WindowWidth, WindowHeight);

		return true;
	}

	void GraphicsManager::Finalize()
	{
		glfwTerminate();
	}

	void GraphicsManager::Tick()
	{
		while (!glfwWindowShouldClose(m_context))
		{
			glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glfwSwapBuffers(m_context);
			glfwPollEvents();
		}
	}
}