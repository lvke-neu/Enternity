#include "OpenglWindow.h"
#include "../Core/Log/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enternity
{
	OpenglWindow::OpenglWindow(const OpenglWindowDescription& desc)
	{
		if (!glfwInit())
		{
			LOG_ERROR("glfw init failed");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		m_context = glfwCreateWindow(desc.Width, desc.Height, desc.Title, nullptr, nullptr);
		if (!m_context)
		{
			LOG_ERROR("glfwWindow create failed");
			return;
		}
		glfwMakeContextCurrent(m_context);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("glad init failed");
			return ;
		}

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, desc.Width, desc.Height);

		LOG_INFO((char*)glGetString(GL_VERSION));
		LOG_INFO((char*)glGetString(GL_VENDOR));
		LOG_INFO((char*)glGetString(GL_RENDERER));
	}

	OpenglWindow::~OpenglWindow()
	{
		glfwTerminate();
	}

	bool OpenglWindow::windowShouldClose()
	{
		return glfwWindowShouldClose(m_context);
	}

	void OpenglWindow::update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_context);
	}
}