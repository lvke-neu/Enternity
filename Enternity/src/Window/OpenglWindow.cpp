#include "OpenglWindow.h"
#include "Log/Log.h"
#include "TestDrawable/Triangle.h"
#include <GLFW/glfw3.h>

BEGIN_ENTERNITY

void OnResize(GLFWwindow* context, int width, int height)
{
	glViewport(0, 0, width, height);
	LOG_INFO("Resize:" + std::to_string(width) + "," + std::to_string(height));
}

void KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		LOG_INFO(std::to_string(key) + " release");
	}

	if (action == GLFW_PRESS)
	{
		LOG_INFO(std::to_string(key) + " press");
	}
}

void MouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_RELEASE)
	{
		LOG_INFO(std::to_string(button) + " release");
	}

	if (action == GLFW_PRESS)
	{
		LOG_INFO(std::to_string(button) + " press");
	}
}

void MouseMoveEvent(GLFWwindow* window, double xpos, double ypos)
{
	LOG_INFO("mouse pos:" + std::to_string(xpos) + "," + std::to_string(ypos));
}


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
	//glfwInit
	if (!glfwInit())
	{
		LOG_ERROR("glfw Init failed");
		return false;
	}

	//contex
	m_context = glfwCreateWindow(m_widowDesc.width, m_widowDesc.height, m_widowDesc.title.c_str(), nullptr, nullptr);
	if (!m_context)
	{
		LOG_ERROR("glfwWindow create failed");
		return false;
	}
	glfwMakeContextCurrent(m_context);

	//initialize glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		//std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//all kind of callback
	glViewport(0, 0, m_widowDesc.width, m_widowDesc.height);
	glfwSetFramebufferSizeCallback(m_context, OnResize);
	glfwSetKeyCallback(m_context, KeyEvent);
	glfwSetMouseButtonCallback(m_context, MouseButtonEvent);
	glfwSetCursorPosCallback(m_context, MouseMoveEvent);

	
	return true;
}

void OpenglWindow::Run()
{
	Triangle triangle;
	while (!glfwWindowShouldClose(m_context))
	{
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw
		triangle.draw();

		glfwSwapBuffers(m_context);
		glfwPollEvents();
	}
}

END_ENTERNITY
