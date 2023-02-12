#include "OpenglWindow.h"
#include "Core/Log/Log.h"
#include "Core/Basic/Macro.h"
#include "Function/Render/RenderSystem.h"
#include "Function/Scene/SceneManager.h"
#include "Function/Scene/Camera3D.h"
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
		//don't Limit frame count
		glfwSwapInterval(0);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("glad init failed");
			return;
		}
		
		CHECK_GL_CALL(glEnable(GL_DEPTH_TEST));
		CHECK_GL_CALL((0, 0, desc.Width, desc.Height));

		glfwSetWindowSizeCallback(m_context, Resize);

		LOG_INFO((char*)glGetString(GL_VERSION));
		LOG_INFO((char*)glGetString(GL_VENDOR));
		LOG_INFO((char*)glGetString(GL_RENDERER));

		Resize(m_context, desc.Width, desc.Height);
	}

	OpenglWindow::~OpenglWindow()
	{
		glfwTerminate();
	}

	bool OpenglWindow::windowShouldClose()
	{
		return glfwWindowShouldClose(m_context);
	}
	void OpenglWindow::setTitle(const char* title)
	{
		glfwSetWindowTitle(m_context, title);
	}

	void OpenglWindow::swapBuffers()
	{
		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}

	void OpenglWindow::Resize(GLFWwindow* window, int width, int height)
	{
		SceneManager::GetInstance().setFrustum(Frustum{ PI / 6.0f, static_cast<float>(width) / height, 1.0f, 1000.0f });
		RenderSystem::GetInstance().setViewPort(width, height);
		LOG_INFO("Resize: width = {0}, height = {1}", width, height);
	}
}