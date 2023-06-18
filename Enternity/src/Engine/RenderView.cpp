#include "RenderView.h"
#include "Log.h"
#include "Common/Macro.h"
#include "Editor/UiRender.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Enternity
{
	RenderView::RenderView(unsigned int width, unsigned int height, const char* title)
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

		m_context = glfwCreateWindow(width, height, title, nullptr, nullptr);
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
		CHECK_GL_CALL(glViewport(0, 0, width, height));

		//glfwSetWindowSizeCallback(m_context, Resize);
		//glfwSetKeyCallback(m_context, KeyTrigger);
		//glfwSetMouseButtonCallback(m_context, MouseTrigger);
		//glfwSetCursorPosCallback(m_context, MouseMove);

		LOG_INFO((char*)glGetString(GL_VERSION));
		LOG_INFO((char*)glGetString(GL_VENDOR));
		LOG_INFO((char*)glGetString(GL_RENDERER));

		m_uiRender = new UiRender(m_context);
	}

	RenderView::~RenderView()
	{
		SAFE_DELETE_SET_NULL(m_uiRender);
		glfwTerminate();
	}

	bool RenderView::windowShouldClose()
	{
		return glfwWindowShouldClose(m_context);
	}

	void RenderView::swapBuffers()
	{
		m_uiRender->onUpdatetime();
		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}

	void RenderView::setTitle(const char* title)
	{
		glfwSetWindowTitle(m_context, title);
	}
}