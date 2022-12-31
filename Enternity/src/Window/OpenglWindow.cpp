#include "OpenglWindow.h"
#include "Log/Log.h"

BEGIN_ENTERNITY

OpenglWindow::OpenglWindow()
{
	m_widowDesc.width = 800;
	m_widowDesc.height = 600;
	m_widowDesc.title = "OpenglWindow";
}

OpenglWindow::OpenglWindow(const WindowDescription& widowDesc):
	m_widowDesc(widowDesc)
{

}

OpenglWindow::~OpenglWindow()
{
	glfwTerminate();
}

bool OpenglWindow::Initialize()
{
	if (!glfwInit())
	{
		LOG_ERROR("glfw Init failed");
		return false;
	}

	m_context = glfwCreateWindow(m_widowDesc.width, m_widowDesc.height, m_widowDesc.title.c_str(), nullptr, nullptr);
	if (!m_context)
	{
		LOG_ERROR("glfwWindow create failed");
		return false;
	}

	glfwMakeContextCurrent(m_context);
	return true;

}

void OpenglWindow::Run()
{
	while (!glfwWindowShouldClose(m_context))
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}
}

END_ENTERNITY
